#include "mdspan_type_util.hpp"
#ifdef BLOCKED
#include "blocked.hpp"
#else
#include "non_blocked.hpp"
#endif

#include <algorithm>
#include <chrono>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <numeric>
#include <vector>

constexpr size_t NEPOCHS = 11;

namespace cross_stencil {
/// Initialize a 2D mdpsan of double with values in the range [0.0, 1.0).
auto init(mdspan_2d<double> mdspn) -> void {
    for (size_t i = 1; i < mdspn.extent(0) - 2; ++i) {
        for (size_t j = 1; j < mdspn.extent(1) - 2; ++j) {
            mdspn(i, j) = drand48();
        }
    }
}
} // namespace cross_stencil

auto main(int argc, char* argv[]) -> int {
    if (argc < 3) {
        fmt::print(stderr, "Usage: {} <DIM_X> <DIM_Y> [BLOCK_X] [BLOCK_Y]\n", argv[0]);
        return -1;
    }

    size_t const DIM_X = static_cast<size_t>(std::atoi(argv[1]));
    size_t const DIM_Y = static_cast<size_t>(std::atoi(argv[2]));
#ifdef BLOCKED
    size_t BLOCK_X = 512;
    size_t BLOCK_Y = 512;
    if (argc >= 4) {
        BLOCK_X = std::atoi(argv[3]);
        if (argc >= 5) { BLOCK_Y = std::atoi(argv[4]); }
    }
#endif

    std::vector<double> input((DIM_X + 2) * (DIM_Y + 2));
    std::vector<double> output((DIM_X + 2) * (DIM_Y + 2));
    fmt::print(stderr, "{}x{}: alloc...\r", DIM_X, DIM_Y);
    Kokkos::mdspan ms_in{ input.data(), Kokkos::extents{ DIM_X + 2, DIM_Y + 2 } };
    Kokkos::mdspan ms_out{ output.data(), Kokkos::extents{ DIM_X + 2, DIM_Y + 2 } };

    fmt::print(stderr, "{}x{}: init...\r", DIM_X, DIM_Y);
    cross_stencil::init(ms_in);

    std::array<std::chrono::duration<double>, NEPOCHS> epochs;
#ifdef BLOCKED
    fmt::print(stderr, "Blocked: warmup...\r");
    cross_stencil::run_blocked(ms_out, ms_in, BLOCK_X, BLOCK_Y);

    fmt::print(stderr, "Blocked: benchmark...\r");
    for (size_t it = 0; it < NEPOCHS; ++it) {
        auto t0 = std::chrono::high_resolution_clock::now();
        cross_stencil::run_blocked(ms_out, ms_in, BLOCK_X, BLOCK_Y);
        auto t1 = std::chrono::high_resolution_clock::now();
        epochs[it] = t1 - t0;
    }
#else
    fmt::print(stderr, "Non-blocked: warmup...\r");
    cross_stencil::run(ms_out, ms_in);

    fmt::print(stderr, "Non-blocked: benchmark...\r");
    for (size_t it = 0; it < NEPOCHS; ++it) {
        auto t0 = std::chrono::high_resolution_clock::now();
        cross_stencil::run(ms_out, ms_in);
        auto t1 = std::chrono::high_resolution_clock::now();
        epochs[it] = t1 - t0;
    }
#endif

    auto mean_time =
        std::accumulate(epochs.begin(), epochs.end(), std::chrono::duration<double>{ 0.0 })
        / static_cast<double>(NEPOCHS);
    auto sdev = 0.0;
    std::for_each(epochs.begin(), epochs.end(), [&](auto e){
      sdev += (e.count() - mean_time.count()) * (e.count() - mean_time.count());
    });
    sdev /= static_cast<double>(NEPOCHS - 1);
    sdev = std::sqrt(sdev) * 100.0 / mean_time.count();

#ifdef BLOCKED
    fmt::print("Blocked: {:.3} +/- {:.2}%\n", mean_time, sdev);
#else
    fmt::print("Non-blocked: {:.3} +/- {:.2}%\n", mean_time, sdev);
#endif

    return 0;
}
