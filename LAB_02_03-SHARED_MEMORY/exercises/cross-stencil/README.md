# Cache blocking


## Pre-requesites

Fetch the Kokkos reference implementation of C++23's `mdspan`:
```sh
git submodule update --init --recursive
```

Ensure you also have:
- CMake 3.16+
- A C++20 conforming compiler supporting OpenMP
- the `{fmt}` library v10+


## Build

Build the program using CMake:
```sh
cmake -S . -B <BUILD_DIR> [-DCMAKE_CXX_FLAGS='-DBLOCKED' ...]
cmake --build <BUILD_DIR>
```


## Run

Run the programm by passing the matrix's and block dimensions as arguments:
```sh
./<BUILD_DIR>/cross-stencil <DIM_X> <DIM_Y> [BLOCK_X] [BLOCK_Y]
```
