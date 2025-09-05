module;
//#include "src/gui/trs2.h"
#include <vector>
//module Globals;
import Globals; 

import Const;

ParmS P{};
TRS2* GUI = nullptr;

std::vector<long> Data;                // single definition
void InitData() {
    Data.resize(static_cast<std::size_t>(P.Chann.Num));
}
