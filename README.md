# apache2_log_alanyzer

Apache2_log_analyzer is a tiny utility tool to anlyze apache2 log file(s).

## Clone

This repositry use git submodule. So, **don't forget to pass `--recursive`** when clone. Or, call `git submodule update --init`.

```
git clone --recursive https://github.com/yumetodo/apache2_log_alanyzer.git
```

or

```
git clone https://github.com/yumetodo/apache2_log_alanyzer.git
cd apache2_log_alanyzer
git submodule update --init
```

## Requirement

- C++ compiler that supports C++17(gcc, clang, msvc...)
- Some task runner cmake supports. ex.) GNU make, ninja, MSBuild, etc...
- cmake 3.10.0 or later([to support `/std:` flag for msvc](https://gitlab.kitware.com/cmake/cmake/-/issues/16482))
- network access to automatically download dependency

## Build and test(Unix like environment)

```
mkdir build
cd build
cmake ..
make
./apache2_log_alanyzer --help
```

For windows msys2 enviroment, `-G "MSYS Makefiles"` will be required for cmake.

To use `clang` in most enviroment, pass `-DCMAKE_CXX_COMPILER=clang++` to cmake.

To build and execute test:

```
make run_test
```

## build(Windows + Visual Studio)

It's recommended to use `cmake-gui.exe`. There are too many documents to build on WWW so that search and watch it. No special configuration is required.

## Usage

You can watch help by passing `--help`

```
apache2_log_alanyzer --help
```

example:

```
cd build
./apache2_log_analyzer.exe count_by_hour ../docs/log_example.txt
./apache2_log_analyzer.exe count_by_remote --take 4 ../docs/log_example.txt
./apache2_log_analyzer.exe count_by_remote --since "2020-6-30 12:40:00 +0900" --until "2020-6-30 15:00:00 +0900" ../docs/log_example.txt
```