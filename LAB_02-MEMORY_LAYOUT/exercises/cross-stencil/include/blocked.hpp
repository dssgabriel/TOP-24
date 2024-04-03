#pragma once

#include "mdspan_type_util.hpp"

namespace cross_stencil {
/// Compute a 5-points cross stencil using cache blocking.
///                        in[i,j-1] +
/// out[i,j] = in[i-1,j] +  in[i,j]  + in[i+1,j] +
///                        in[i,j+1]
auto run_blocked(
    mdspan_2d<double> ms_out,
    mdspan_2d<double> const ms_in,
    size_t block_x,
    size_t block_y
) -> void;
} // namespace cross_stencil
