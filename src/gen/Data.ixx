module;  // global module fragment for legacy includes if any

import <vector>;
import <span>;
import <mdspan>;
import <cstdint>;
import <algorithm>;
import <utility>;
import <stdexcept>;

export module Data;



import Const; // for T_DATA, T_SUB, T_HEAD, SPC_BANK_DIM, etc. (?filecite?turn6file0?)

// A compact, cache-friendly, RAII-managed storage for all acquisition arrays.
// - Uses flat std::vector for storage (minimal fragmentation, contiguous walks)
// - Exposes lightweight std::mdspan views for 2D/3D access
// - Keeps API close to legacy D.* while avoiding double indirections
export class Data {
public:
    using index_t = std::size_t;
    using u16 = std::uint16_t;

    // Sizes of the problem (copied from P at configuration time)
    struct Sizes {
        int frames = 0;   // P.Frame.Num
        int pages = 0;   // P.Num.Page
        int boards = 0;   // P.Num.Board
        int det = 0;   // P.Num.Det
        int ch = 0;   // P.Chann.Num
    };

    // A minimal feature mask to mirror conditional allocations in the C code
    struct Features {
        bool measurement_mode = false;  // (P.Contest.Run == CONTEST_MEAS)
        bool subtract_enabled = false;  // P.Spc.Subtract
        bool subheader = false;  // P.Info.SubHeader
        bool bank_needed = false;  // e.g. MOXY/Spcm paths
        bool spcm_bus = false;  // allocate BusSpcm
        int  bank_dim = SPC_BANK_DIM; // default
    };

    // --- configure/teardown -------------------------------------------------
    void configure(const Sizes s, const Features f) {
        if (s.frames < 0 || s.pages < 0 || s.boards < 0 || s.det < 0 || s.ch < 0)
            throw std::invalid_argument("Data.configure: negative sizes");

        sizes_ = s; feat_ = f;
        const index_t total_det = static_cast<index_t>(s.boards) * static_cast<index_t>(s.det);
        const index_t total_chan = static_cast<index_t>(s.ch);
        const index_t total_pages = static_cast<index_t>(s.pages);
        const index_t total_frames = static_cast<index_t>(s.frames);

        // Always present paths ------------------------------------------------
        osc_.assign(total_det * total_chan, T_DATA{});
        buffer_.assign(static_cast<index_t>(s.boards) * (static_cast<index_t>(s.det) * total_chan), T_DATA{});
        busSpcm_.assign(f.spcm_bus ? total_det * total_chan : 0, u16{});
        last_.assign(f.subtract_enabled ? total_chan : 0, T_DATA{});

        // Measurement-only paths ---------------------------------------------
        if (f.measurement_mode) {
            data_.assign(total_frames * total_pages * total_chan, T_DATA{});
            bank_.assign(f.bank_needed ? static_cast<index_t>(s.boards) * static_cast<index_t>(f.bank_dim) : 0, T_DATA{});
            sub_.assign(f.subheader ? total_frames * total_pages : 0, T_SUB{});
        }
        else {
            data_.clear(); bank_.clear(); sub_.clear();
        }
    }

    void release() { *this = Data{}; }

    // --- header / subheader -------------------------------------------------
    T_HEAD* head()       noexcept { return head_; }
    const T_HEAD* head() const noexcept { return head_; }
    void          set_head(T_HEAD* h)   noexcept { head_ = h; }

    // 2D subheader view [frames, pages]
    auto sub() noexcept {
        using ext2 = std::extents<index_t, std::dynamic_extent, std::dynamic_extent>;
        return std::mdspan<T_SUB, ext2>(sub_.data(), sizes_cast(sizes_.frames), sizes_cast(sizes_.pages));
    }
    auto sub() const noexcept {
        using ext2 = std::extents<index_t, std::dynamic_extent, std::dynamic_extent>;
        return std::mdspan<const T_SUB, ext2>(sub_.data(), sizes_cast(sizes_.frames), sizes_cast(sizes_.pages));
    }

    // --- main data views ----------------------------------------------------
    // Osc: [boards*det, ch]
    auto osc() noexcept {
        using ext2 = std::extents<index_t, std::dynamic_extent, std::dynamic_extent>;
        return std::mdspan<T_DATA, ext2>(osc_.data(), totalDet(), ch());
    }
    auto osc() const noexcept {
        using ext2 = std::extents<index_t, std::dynamic_extent, std::dynamic_extent>;
        return std::mdspan<const T_DATA, ext2>(osc_.data(), totalDet(), ch());
    }

    // Buffer: [boards, det*ch]
    auto buffer() noexcept {
        using ext2 = std::extents<index_t, std::dynamic_extent, std::dynamic_extent>;
        return std::mdspan<T_DATA, ext2>(buffer_.data(), boards(), det() * ch());
    }
    auto buffer() const noexcept {
        using ext2 = std::extents<index_t, std::dynamic_extent, std::dynamic_extent>;
        return std::mdspan<const T_DATA, ext2>(buffer_.data(), boards(), det() * ch());
    }

    // Data cube: [frames, pages, ch]
    auto data() noexcept {
        using ext3 = std::dextents<index_t, 3>;
        return std::mdspan<T_DATA, ext3>(data_.data(), sizes_cast(sizes_.frames), sizes_cast(sizes_.pages), ch());
    }
    auto data() const noexcept {
        using ext3 = std::dextents<index_t, 3>;
        return std::mdspan<const T_DATA, ext3>(data_.data(), sizes_cast(sizes_.frames), sizes_cast(sizes_.pages), ch());
    }

    // Bank: [boards, bank_dim]
    auto bank() noexcept {
        using ext2 = std::extents<index_t, std::dynamic_extent, std::dynamic_extent>;
        return std::mdspan<T_DATA, ext2>(bank_.data(), boards(), bankDim());
    }
    auto bank() const noexcept {
        using ext2 = std::extents<index_t, std::dynamic_extent, std::dynamic_extent>;
        return std::mdspan<const T_DATA, ext2>(bank_.data(), boards(), bankDim());
    }

    // One curve view into the 3D data cube (for convenience)
    std::span<T_DATA> curve(int frame, int page) noexcept {
        const index_t offset = (sizes_cast(frame) * sizes_cast(sizes_.pages) + sizes_cast(page)) * ch();
        return std::span<T_DATA>(data_.data() + offset, ch());
    }

    // Last / BusSpcm linear views
    std::span<T_DATA> last() noexcept { return last_; }
    std::span<const T_DATA> last() const noexcept { return last_; }
    std::span<u16> bus_spcm() noexcept { return busSpcm_; }
    std::span<const u16> bus_spcm() const noexcept { return busSpcm_; }

    // Sizes accessors (no imports of Globals needed here)
    int frames() const noexcept { return sizes_.frames; }
    int pages()  const noexcept { return sizes_.pages; }
    int boards() const noexcept { return sizes_.boards; }
    int det()    const noexcept { return sizes_.det; }
    int ch()     const noexcept { return sizes_.ch; }
    index_t totalDet()  const noexcept { return static_cast<index_t>(sizes_.boards) * static_cast<index_t>(sizes_.det); }
    int     bankDim()   const noexcept { return feat_.bank_dim; }

    // Utilities --------------------------------------------------------------
    void zero_all() {
        std::ranges::fill(osc_, T_DATA{});
        std::ranges::fill(buffer_, T_DATA{});
        std::ranges::fill(last_, T_DATA{});
        std::ranges::fill(busSpcm_, u16{});
        std::ranges::fill(data_, T_DATA{});
        std::ranges::fill(bank_, T_DATA{});
        // sub_ intentionally not zeroed: keep metadata unless you really need to wipe it
    }

private:
    static index_t sizes_cast(int v) noexcept { return static_cast<index_t>(static_cast<unsigned>(v)); }

    // flat storages
    std::vector<T_DATA> osc_;     // (boards*det) * ch
    std::vector<T_DATA> buffer_;  // boards * (det*ch)
    std::vector<T_DATA> data_;    // frames * pages * ch (meas only)
    std::vector<T_DATA> bank_;    // boards * bank_dim (optional)
    std::vector<T_DATA> last_;    // ch (optional)
    std::vector<u16>    busSpcm_; // det * ch (optional)

    std::vector<T_SUB>  sub_;     // frames * pages (optional)
    T_HEAD* head_ = nullptr; // opaque pointer, managed elsewhere if needed

    Sizes    sizes_{};
    Features feat_{};
};

// Export a single global instance (import this module wherever you need Data)
export Data D; // one-definition; no "extern" gymnastics needed
