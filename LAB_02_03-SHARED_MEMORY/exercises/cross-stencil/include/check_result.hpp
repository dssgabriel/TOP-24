#pragma once

#include "mdspan_type_util.hpp"

namespace cross_stencil {
/// Check if the results between the non-blocked and cache-blocked implementations match.
auto check_result(
    mdspan_2d<double> const& result_non_blocked, mdspan_2d<double> const& result_blocked
) -> void;
} // namespace cross_stencil
