#pragma once

#include <cstdint>
#include <vector>

namespace sum_reduce {
/// Sequential 32-bit integer sum reduction.
auto sequential(std::vector<int32_t> const& vec) -> int64_t;
} // namespace sum_reduce
