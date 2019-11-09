# primecount build instructions

## Prerequisites

You need to have installed a C++ compiler which supports C++11 (or later) and CMake ≥ 3.4.

<table>
    <tr>
        <td><b>Debian/Ubuntu:</b></td>
        <td><code>sudo apt install g++ cmake</code></td>
    </tr>
    <tr>
        <td><b>Fedora:</b></td>
        <td><code>sudo dnf install gcc-c++ cmake</code></td>
    </tr>
    <tr>
        <td><b>openSUSE:</b></td>
        <td><code>sudo zypper install gcc-c++ cmake</code></td>
    </tr>
    <tr>
        <td><b>Arch Linux:</b></td>
        <td><code>sudo pacman -S gcc cmake</code></td>
    </tr>
</table>

## Unix-like OSes

Open a terminal, cd into the primecount directory and run:

```bash
cmake .
make -j
```

## macOS

On macOS the default C++ compiler that can be installed using ```xcode-select --install```
does not support OpenMP multi-threading. Hence I suggest installing an alternative
C++ compiler that supports OpenMP.

```bash
# Install C++ compiler with OpenMP support
brew install cmake llvm libomp

# Build primecount with OpenMP
LIBRARY_PATH=$(brew --prefix llvm)/lib CXX=$(brew --prefix llvm)/bin/clang++ cmake .
make -j
```

## MinGW/MSYS2 (Windows)

Open a terminal, cd into the primecount directory and run:

```bash
cmake -G "Unix Makefiles" .
make -j
```

## Microsoft Visual C++

First install [Visual Studio](https://visualstudio.microsoft.com/downloads/)
(includes CMake) on your Windows PC. Then go to the start menu, select Visual
Studio and open a **x64 Command Prompt**. Now cd into the primecount directory
and run the commands below:

```bash
# Use 'cmake -G' to find your Visual Studio version
cmake -G "Visual Studio 15 2017 Win64" .
cmake --build . --config Release
```

## Run the tests

Open a terminal, cd into the primecount directory and run:

```bash
cmake -DBUILD_TESTS=ON .
make -j
ctest
```

## CMake configure options

By default the primecount binary, the static libprimecount and
libprimesieve will be built. The build options can be modified at
the configure step using e.g. ```cmake . -DBUILD_TESTS=ON```.

```CMake
option(WITH_POPCNT         "Enable POPCNT instruction"   ON)
option(WITH_LIBDIVIDE      "Use libdivide.h"             ON)
option(WITH_OPENMP         "Enable OpenMP support"       ON)
option(BUILD_PRIMECOUNT    "Build primecount binary"     ON)
option(BUILD_LIBPRIMESIEVE "Build libprimesieve"         ON)
option(BUILD_SHARED_LIBS   "Build shared libprimecount"  OFF)
option(BUILD_STATIC_LIBS   "Build static libprimecount"  ON)
option(BUILD_TESTS         "Build test programs"         OFF)
```