#!/usr/bin/env python

import subprocess
import sys
import matplotlib.pyplot as plt
from typing import List, Tuple
from matplotlib import ticker


def bench_strong_scalability(bin_path: str, max_threads=64) -> List[Tuple[int, float]]:
    thrd = 1
    data = [(thrd, 1.0)]
    time_ref = float(
        subprocess.check_output([bin_path, str(1000), str(1000), str(thrd)])
        .decode()
        .strip()
        .split()[1]
    )
    while thrd < max_threads:
        thrd *= 2
        print(
            f"Strong scaling benchmark: {thrd} threads",
            end="\r",
        )
        time = float(
            subprocess.check_output([bin_path, str(1000), str(1000), str(thrd)])
            .decode()
            .strip()
            .split()[1]
        )
        data.append((thrd, time_ref / time))

    print("")
    return data


def bench_weak_scalability(
    bin_path: str, max_threads=64, max_dim=1000
) -> List[Tuple[int, float]]:
    thrd = 1
    dim_x = 100
    dim_y = 100
    data = [(thrd, 1.0)]
    time_ref = float(
        subprocess.check_output([bin_path, str(dim_x), str(dim_y), str(thrd)])
        .decode()
        .strip()
        .split()[1]
    )
    while thrd < max_threads and (dim_x <= max_dim or dim_y <= max_dim):
        thrd *= 2
        if dim_x <= max_dim:
            dim_x *= 2
        else:
            dim_y *= 2

        print(f"Weak scalability benchmark: {thrd} threads", end="\r")
        time = float(
            subprocess.check_output([bin_path, str(dim_x), str(dim_y), str(thrd)])
            .decode()
            .strip()
            .split()[1]
        )
        data.append((thrd, time_ref / time))

    print("")
    return data


def plot_results(data: List[Tuple[int, float]], title: str, mode: str) -> None:
    thrds, times = zip(*data)

    plt.figure()
    if mode == "strong":
        plt.plot(
            [thrds[0], thrds[-1]],
            [times[0], times[0] * thrds[-1]],
            color="r",
            linestyle="-",
            label="Ideal speedup",
        )
        plt.ylim(ymin=0.8)
    elif mode == "weak":
        plt.axhline(y=1, color="r", linestyle="-", label="Ideal efficiency")
        plt.ylim(ymin=-0.2, ymax=1.2)
    plt.plot(
        thrds,
        times,
        marker="o",
        linestyle="-",
        label=f'Real {"speedup" if mode == "strong" else "efficiency"}',
    )

    plt.xscale("log", base=2)
    plt.xticks(list(thrds))
    plt.xlabel("Number of OpenMP threads")
    plt.ylabel(f'{"Speedup" if mode == "strong" else "Efficiency"}')
    plt.title(title)
    plt.grid(True)
    plt.legend()

    plt.savefig(f'{title.lower().replace(" ", "_")}.png')
    plt.show()


def main() -> int:
    if len(sys.argv) != 3:
        print("Usage: python bench.py <BIN> <MODE>")
        sys.exit(1)

    bin = sys.argv[1]
    mode = sys.argv[2]
    if mode == "strong":
        data = bench_strong_scalability(bin, 8)
        plot_results(data, "Mesh strong scaling speedup", "strong")
    elif mode == "weak":
        data = bench_weak_scalability(bin, 8)
        plot_results(data, "Mesh weak scaling efficiency", "weak")
    else:
        print(
            f"\x1b[1;31merror:\x1b[0m unknown mode `{mode}` (pick one of: [strong, weak])"
        )
        return -1

    return 0


if __name__ == "__main__":
    main()
