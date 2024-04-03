#pragma once

#include "mdspan.hpp"

#include <cstddef>

template <typename T>
using mdspan_2d =
    Kokkos::mdspan<T, Kokkos::extents<size_t, Kokkos::dynamic_extent, Kokkos::dynamic_extent>>;
