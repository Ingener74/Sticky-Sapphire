#pragma once

#include <stdint.h>
#include <vector>

namespace discarded_steel {

struct RgbImage
{
    int32_t rows = 0;
    int32_t cols = 0;
    std::vector<uint8_t> buffer;
};

}

