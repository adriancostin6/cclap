#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include "cclap.h"

// Chose to provide mandatory arguments first, check for correct order
TEST_CASE("How to use the Command-line parser API", "[api-usage]") {
    // Example command line argument string
    int argc = 12;
    const char *argv[] = {
            "/home/adrian/repos/src/cclap/build/bin/cclap",
            "required-arg1",
            "required-arg2",
            "-i",
            "input_file1.txt",
            "input_file2.txt",
            "-o",
            "outfile.txt",
            "--single-switch",
            "-s",
            "--multi-switch-next",
            "-src"
        };

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
