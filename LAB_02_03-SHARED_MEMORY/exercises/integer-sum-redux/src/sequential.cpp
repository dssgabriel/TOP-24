#include "sequential.hpp"

namespace sum_reduce {
auto sequential(std::vector<int32_t> const& vec) -> int64_t {
    size_t vec_size = vec.size();
    int64_t sum = 0;
    for (size_t i = 0; i < vec_size; ++i) {
        // ???
    }
    return sum;
}
} // namespace sum_reduce
