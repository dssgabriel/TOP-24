#include "blocked.hpp"

#include <cassert>
#include <cstddef>

namespace cross_stencil {
auto run_blocked(
    mdspan_2d<double> ms_out,
    mdspan_2d<double> const ms_in,
    size_t block_x,
    size_t block_y
) -> void {
    assert(ms_out.extent(0) == ms_in.extent(0) && ms_out.extent(1) == ms_in.extent(1));

#pragma omp parallel for
    for (size_t bi = 1; bi < ms_out.extent(0) - 2; bi += block_x) {
        for (size_t bj = 1; bj < ms_out.extent(1) - 2; bj += block_y) {
            size_t bi_end = std::min(bi + block_x, ms_out.extent(0) - 2);
            size_t bj_end = std::min(bj + block_y, ms_out.extent(1) - 2);
            for (size_t i = bi; i < bi_end; ++i) {
                for (size_t j = bj; j < bj_end; ++j) {
                    ms_out(i, j) = ms_in(i - 1, j) + ms_in(i, j - 1) + ms_in(i, j) + ms_in(i, j + 1)
                                   + ms_in(i + 1, j);
                    ms_out(i, j) /= ms_in(i, j);
                }
            }
        }
    }
}
} // namespace cross_stencil
