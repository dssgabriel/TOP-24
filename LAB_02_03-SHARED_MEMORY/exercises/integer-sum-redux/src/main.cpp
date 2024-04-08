#include "cycle.h"
#include "sequential.hpp"

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fmt/core.h>
#include <functional>
#include <numeric>
#include <span>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#define NEPOCHS 11

namespace utils {
template <typename T> requires std::is_integral_v<T>
auto initialize(std::span<T> s) -> void {
    for (auto& e : s) {
        e = static_cast<T>(mrand48() % 100);
    }
}

template <typename T> auto print(std::span<T> s) -> void {
    for (auto& e : s) {
        fmt::print("{} ", e);
    }
    fmt::print("\n");
}

auto ticks_per_elem(ticks t0, ticks t1, size_t nelems) -> double {
    return static_cast<double>(t1 - t0) / static_cast<double>(nelems);
}

auto mean(std::array<double, NEPOCHS> const& epochs) -> double {
    return std::accumulate(epochs.begin(), epochs.end(), 0.0) / static_cast<double>(NEPOCHS);
}

auto standard_deviation(std::array<double, NEPOCHS> const& epochs, double mean) {
    auto tmp = 0.0;
    std::for_each(epochs.begin(), epochs.end(), [&](auto e) { tmp += (e - mean) * (e - mean); });
    tmp /= static_cast<double>(NEPOCHS - 1);
    return std::sqrt(tmp) * 100.0 / mean;
}

auto check_result(std::string_view name, int64_t reference, int64_t result) {
    if (reference != result) {
        fmt::print(
            stderr,
            "\n\x1b[1;31mfailure:\x1b[0m {}: expected {} but got {}\n",
            name,
            reference,
            result
        );
        std::abort();
    } else {
        fmt::print("result: {}\n", result);
    }
}
} // namespace utils

template <typename Fn, typename... Args>
auto benchmark(std::string_view name, size_t nelems, Fn fn, Args&&... args)
    -> std::invoke_result_t<Fn, Args...>
{
    std::array<double, NEPOCHS> epochs;
    std::invoke_result_t<Fn, Args...> res;

    for (size_t it = 0; it < NEPOCHS; ++it) {
        auto t0    = /* ??? */;
        res = std::invoke(fn, std::forward<Args>(args)...);
        auto t1    = /* ??? */;
        epochs[it] = /* ??? */;
    }

    auto mean = utils::mean(epochs);
    auto sdev = utils::standard_deviation(epochs, mean);
    fmt::print("{}: {:.3} ticks/element +/- {:.2}%, ", name, mean, sdev);

    return res;
}

auto main(int argc, char* argv[]) -> int {
    if (argc < 2) {
        fmt::print(stderr, "Usage: {} <ARRAY_SIZE>\n", argv[0]);
        return -1;
    }

    auto const N = static_cast<size_t>(std::atoi(argv[1]));
    std::vector<int32_t> vec(N);
    utils::initialize<int32_t>(vec);
    int64_t ref = std::reduce(vec.begin(), vec.end(), 0, std::plus{});

    auto seq = benchmark("Sequential", N, [&]() { return sum_reduce::sequential(vec); });
    utils::check_result("Sequential", ref, seq);

    return 0;
}
