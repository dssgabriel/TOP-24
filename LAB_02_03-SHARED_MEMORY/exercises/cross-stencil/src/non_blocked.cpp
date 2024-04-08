#include "non_blocked.hpp"

#include <cassert>
#include <cstddef>
#include <omp.h>

namespace cross_stencil {
auto run(mdspan_2d<double> ms_out, mdspan_2d<double> const ms_in) -> void {
    assert(ms_out.extent(0) == ms_in.extent(0) && ms_out.extent(1) == ms_in.extent(1));

#pragma omp parallel for
    for (size_t i = 1; i < ms_out.extent(0) - 2; ++i) {
        for (size_t j = 1; j < ms_out.extent(1) - 2; ++j) {
            ms_out(i, j) =
                ms_in(i - 1, j) + ms_in(i, j - 1) + ms_in(i, j) + ms_in(i, j + 1) + ms_in(i + 1, j);
            ms_out(i, j) /= ms_in(i, j);
        }
    }
}
} // namespace cross_stencil
