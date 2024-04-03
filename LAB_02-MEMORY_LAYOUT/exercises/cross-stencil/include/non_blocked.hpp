#pragma once

#include "../ext/mdspan/include/mdspan/mdspan.hpp"

using namespace Kokkos;
using dextents_2d = extents<size_t, dynamic_extent, dynamic_extent>;

namespace cross_stencil {
/// Compute a 5-points cross stencil.
///                        in[i,j-1] +
/// out[i,j] = in[i-1,j] +  in[i,j]  + in[i+1,j] +
///                        in[i,j+1]
auto run(mdspan<double, dextents_2d> ms_out, mdspan<double, dextents_2d> const ms_in) -> void;
} // namespace cross_stencil
