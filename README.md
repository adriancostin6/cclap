# cclap - c++ command line argument parser

Command line argument parser written in C++. Uses C++17, providing a modern API
that allows easily building simple CLI applications. The tool is provided in the
form of a static library that has to be linked into your own project. More instructions
below...

## How to use

``` cpp
#include "cclap.h"

int main(int argc, char *argv[]) {
    cclap::ArgParser ap(argc, argv);
    
    // Retrieve the arguments 
    const cclap::ArgVector& arguments = ap.args(); 
    const cclap::NamedPairVector& flags = ap.flags(); 
    const cclap::ArgVector& switches = ap.switches();

    // Printing all the arguments, demo on how to access each one
    for (auto arg: arguments) {
        std::cout << arg << " ";
    }
    for (auto flag: flags) {
        std::cout << "-" << flag.first << " ";
        for (auto value: flag.second) {
            std::cout << value << " ";
        }
    }
    for (auto s: switches) {
        std::cout << "-" << s << " ";
    } 
    std::cout << std::endl;
    
}
```

## How to build the library

### Build dependencies

- CMake (>= v.3.11)
- Compiler that supports building C++ 17 code

### Building the project

Use the following commands to build the project into a static library.

``` bash
git clone https://github.com/adriancostin6/cclap.git
cd cclap
mkdir build 
cd build
cmake .. -DBUILD_TESTS=true # providing this flag enables building tests as well
make
```

After a successful build, run the unit-tests using: `ctest`

## Integrating into your own project

In order to use the library in your own project, follow the steps below.

### CMake integration

A barebones example CMake file has been provided below. Using this along with
the example-usage.cpp found in the [./test](test) directory should provide an introduction
into how to use the API to parse command line arguments.

``` cmake
cmake_minimum_required(VERSION 3.11)
project(example LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    catch2
    GIT_REPOSITORY    https://github.com/adriancostin6/cclap.git
    )
message(STATUS "Fetching cclap...")
FetchContent_MakeAvailable(catch2)

add_executable(example-usage example-usage.cpp)
target_link_libraries(example-usage PRIVATE cclap) 
target_include_directories(example-usage PRIVATE ${CMAKE_SOURCE_DIR}/include)
```

## Building the example

The first step is creating a directory for your project. After doing so, create
a new CMakeLists.txt file containing the template provided above inside it.

The next step involves copying the cclap include directory into your project folder, along with the example.

You should end up with something like this:

```
./
CMakeLists.txt
include/cclap/
example-usage.cpp
```

Afterwards, run the following commands:

```
mkdir build
cd build
cmake ..
make
```

