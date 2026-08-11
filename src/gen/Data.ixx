module;

#include <atomic>
#include <cstdint>
#include <cstring>
#include <thread>
#include <vector>
#include <mutex>
#include <memory>

export module Data;

import Globals;
import Const;

export
{
    using TYPE_DATA = std::uint32_t;

    class Data
    {
    public:

        int NumElem=P.Num.Board*P.Num.Det*P.Bins.Num;
        int NumAcq=128;
        int NumSlice=P.Loop[4].Num;

        std::vector<TYPE_DATA*> Ring;
        std::vector<TYPE_DATA*> Archive;
        std::vector<TYPE_DATA> Temp;


        std::vector<TYPE_DATA> RingData;
        std::vector<TYPE_DATA> ArchiveData;

        std::atomic<std::uint64_t> produced{ 0 };
        std::atomic<std::uint64_t> consumed{ 0 };


        Data(void)
        {
            // allocate contiguous storage
            RingData.resize(static_cast<size_t>(NumAcq) * static_cast<size_t>(NumElem));
            ArchiveData.resize(static_cast<size_t>(NumSlice) * static_cast<size_t>(NumElem));
            Temp.resize(static_cast<size_t>(NumElem));

            // allocate pointer tables
            Ring.resize(static_cast<size_t>(NumAcq));
            Archive.resize(static_cast<size_t>(NumSlice));

            // set pointers into the contiguous storage
            for (int i = 0; i < NumAcq; ++i)
                Ring[static_cast<size_t>(i)] = RingData.data() + static_cast<size_t>(i) * static_cast<size_t>(NumElem);

            for (int i = 0; i < NumSlice; ++i)
                Archive[static_cast<size_t>(i)] = ArchiveData.data() + static_cast<size_t>(i) * static_cast<size_t>(NumElem);
        }

        // default destructor is fine (vectors free memory automatically)

        void Reset()
        {
            produced.store(0, std::memory_order_relaxed);
            consumed.store(0, std::memory_order_relaxed);
        }

    };


    // ========================================================
    // Copy oldest unread acquisition Ring -> Archive
    // ========================================================

    inline void CopyNext(Data* D, int target_slice)
    {
        std::uint64_t n = D->consumed.load(std::memory_order_relaxed);

        while (n >= D->produced.load(std::memory_order_acquire)) // Wait until an acquisition is available
            std::this_thread::yield();
        int first_acq = int(n % D->NumAcq);
        std::memcpy(D->Archive[static_cast<size_t>(target_slice)], D->Ring[static_cast<size_t>(first_acq)], D->NumElem * sizeof(TYPE_DATA));
        std::memcpy(D->Temp.data(), D->Ring[static_cast<size_t>(first_acq)], D->NumElem * sizeof(TYPE_DATA));
        D->consumed.store(n + 1, std::memory_order_relaxed); // This acquisition has now been consumed
    }

    // --------------------------------------------------------
    // Create Data
    // -------------------------------------------------------

    // Global unique pointer to Data instance (exported via the module export block)
    inline std::unique_ptr<Data> D;

    inline Data* initData(void)
    {
        D = std::make_unique<Data>();
        return D.get();
    }

    inline void closeData(void)
    {
        D.reset(); // free the Data instance
    }

} // End of export
