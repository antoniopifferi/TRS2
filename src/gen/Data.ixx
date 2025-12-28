module;  // global module fragment for legacy includes if any

#include <vector>
#include <cstdint>

import Globals;

export module Data;

export class Data {
public:
    std::vector<std::uint32_t> data;

	// initialise data with size P.Bins.Num
	void init() {
		data.resize(static_cast<std::size_t>(P.Bins.Num));
	}	
};

export Data D;
