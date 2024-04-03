#pragma once

#include "../ext/mdspan/include/mdspan/mdspan.hpp"

using namespace Kokkos;
using dextents_2d = extents<size_t, dynamic_extent, dynamic_extent>;

namespace cross_stencil {
/// Check if the results between the non-blocked and cache-blocked implementations match.
auto check_result(
    mdspan<double, dextents_2d> const& result_non_blocked,
    mdspan<double, dextents_2d> const& result_blocked
) -> void;
} // namespace cross_stencil
