cmake_minimum_required(VERSION 3.11)
project(cclap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_BUILD_TYPE Release)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif(CCACHE_FOUND)

if (BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        catch2
        GIT_REPOSITORY    https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.0-preview4
        )
    message(STATUS "Fetching Catch2...")
    FetchContent_MakeAvailable(catch2)

    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    include (CTest)
    include (Catch)
endif()

add_subdirectory(src)
add_subdirectory(test)
