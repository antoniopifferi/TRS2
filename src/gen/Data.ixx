module;  // global module fragment for legacy includes if any

#include <vector>
#include <cstdint>
#include <cstring>

// do not import other modules from the global fragment

export module Data;

import Globals;
import Const;

// Export types expected by other modules
export using T_HEAD = sHeader2;
export using T_SUB = sSubHeader1;

export class Data {
public:
    T_HEAD Head{};

    // contiguous storage for all data: frames * (det * bins)
    std::vector<std::uint32_t> data;

    // Legacy-compatible row pointers: D.Data[frame] -> pointer to first element of that row
    std::vector<std::uint32_t*> Data;

    int frames = 0;
    std::size_t width = 0; // det * bins

    // initialise data with dimensions from P
    void init() {
        frames = static_cast<int>(P.Frame.Num);
        const int det = static_cast<int>(P.Num.Det);
        const std::size_t bins = static_cast<std::size_t>(P.Bins.Num);
        width = static_cast<std::size_t>(det) * bins;
        data.clear();
        data.resize(static_cast<std::size_t>(frames) * width);
        // zero-initialized by vector

        Data.assign(frames, nullptr);
        for (int f = 0; f < frames; ++f) {
            Data[f] = data.data() + static_cast<std::size_t>(f) * width;
        }
    }

    // convenience to get pointer to row
    std::uint32_t* row(int ifr) {
        if (ifr < 0 || ifr >= frames) return nullptr;
        return Data[ifr];
    }
};

export Data D;
