#!/usr/bin/env python

import argparse
import subprocess
import sys
import matplotlib.pyplot as plt
from typing import List, Tuple
from matplotlib import ticker


def bench_strong_scalability(
    bin_path: str, max_threads: int = 64
) -> List[Tuple[int, float]]:
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
    bin_path: str, max_threads: int = 64, max_dim: int = 1000
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

    fig, ax = plt.subplots()
    if mode == "strong":
        ax.plot(
            [thrds[0], thrds[-1]],
            [times[0], times[0] * thrds[-1]],
            color="r",
            linestyle="-",
            label="Ideal speedup",
        )
        ax.set_yscale("log", base=2)
        ax.get_yaxis().set_major_formatter(ticker.ScalarFormatter())
        ax.get_yaxis().set_minor_formatter(ticker.NullFormatter())
    elif mode == "weak":
        ax.axhline(y=1, color="r", linestyle="-", label="Ideal efficiency")
    ax.plot(
        thrds,
        times,
        marker="o",
        linestyle="-",
        label=f'Real {"speedup" if mode == "strong" else "efficiency"}',
    )

    ax.set_xscale("log", base=2)
    ax.set_xticks(list(thrds))
    ax.get_xaxis().set_major_formatter(ticker.ScalarFormatter())
    ax.get_xaxis().set_minor_formatter(ticker.NullFormatter())
    ax.set_xlabel("Number of OpenMP threads")
    ax.set_ylabel(f'{"Speedup" if mode == "strong" else "Efficiency"}')
    ax.set_title(title)
    ax.grid(True)
    ax.legend()

    plt.savefig(f'{title.lower().replace(" ", "_")}.png')
    plt.show()


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Run a scaling benchmark on the `mesh` program"
    )
    parser.add_argument("exec_path", type=str, help="Path to the `mesh` executable")
    parser.add_argument(
        "mode",
        choices=["strong", "weak"],
        help="Benchmarking mode: strong or weak scaling",
    )
    parser.add_argument(
        "-t",
        "--max_threads",
        type=int,
        default=8,
        help="Maximum number of OpenMP threads to use",
    )

    args = parser.parse_args()
    match args.mode:
        case "strong":
            data = bench_strong_scalability(args.exec_path, args.max_threads)
            plot_results(data, "Mesh strong scaling speedup", "strong")
        case "weak":
            data = bench_weak_scalability(args.exec_path, args.max_threads)
            plot_results(data, "Mesh weak scaling efficiency", "weak")
        case _:
            print(
                f"\x1b[1;31merror:\x1b[0m unknown mode `{mode}` (pick one of: [strong, weak])"
            )
            sys.exit(-1)

    return 0


if __name__ == "__main__":
    main()
