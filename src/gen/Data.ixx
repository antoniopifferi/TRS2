module;  // global module fragment for legacy includes if any

#include <vector>
#include <cstdint>

export module Data;

export class Data {
public:
    std::vector<std::uint32_t> data;
};

export Data D;
