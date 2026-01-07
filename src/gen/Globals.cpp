module;
//#include "src/gui/trs2.h"
#include <vector>
//module Globals;
import Globals; 

import Const;

// Definitions moved to the module interface (Globals.ixx) to avoid duplicate symbols.
// This TU only provides other non-global definitions.

std::vector<long> Data;                // single definition
void InitData() {
    Data.resize(static_cast<std::size_t>(P.Chann.Num));
}
