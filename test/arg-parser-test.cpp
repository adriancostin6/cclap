#include <string>

#include <catch2/catch_test_macros.hpp>

#include "cclap/cclap.h"

// Chose to provide mandatory arguments first, check for correct order
TEST_CASE("Right argument order (options last)", "[arg-parser]") {
    int argc = 13;
    const char *argv[] = {
            "/home/adrian/repos/src/cclap/build/test/arg-parser-test",
            "hello",
            "world",
            "test",
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

    auto program_name = ap.program_name();
    auto arguments = ap.args();
    auto flags = ap.flags();
    auto switches = ap.switches();

    REQUIRE(program_name == argv[0]);

    // test size of returned arguments
    REQUIRE(arguments.size() == 3);
    REQUIRE(flags.size() == 2);
    REQUIRE(switches.size() == 6);

    // test for argument equality
    int j=1;
    for (int i = 0; i < arguments.size(); ++i) {
        REQUIRE (arguments[i] == argv[j]);
        ++j;
    }

    auto flag_name1 = flags[0].first;
    auto flag_val1 = flags[0].second;
    auto flag_name2 = flags[1].first;
    auto flag_val2 = flags[1].second;
    REQUIRE(flag_name1 == "i");
    REQUIRE(flag_val1[0] == "input_file1.txt");
    REQUIRE(flag_val1[1] == "input_file2.txt");
    REQUIRE(flag_name2 == "o");
    REQUIRE(flag_val2[0] == "outfile.txt");

    auto switch1 = switches[0];
    auto switch2 = switches[1];
    auto switch3 = switches[2];
    auto switch4 = switches[3];
    auto switch5 = switches[4];
    auto switch6 = switches[5];
    REQUIRE(switch1 == "single-switch");
    REQUIRE(switch2 == "s");
    REQUIRE(switch3 == "multi-switch-next");
    REQUIRE(switch4 == "s");
    REQUIRE(switch5 == "r");
    REQUIRE(switch6 == "c");
} 

// Chose to provide mandatory arguments first, check for wrong order
TEST_CASE("Wrong argument order (options first)", "[arg-parser]") {
    int argc = 12;
    const char *argv[] = {
            "/home/adrian/repos/src/cclap/build/test/arg-parser-test",
            "-i",
            "input_file1.txt",
            "input_file2.txt",
            "-o",
            "outfile.txt",
            "--single-switch",
            "-s",
            "--multi-switch-next",
            "-src",
            "hello",
            "world",
            "test"
        };

    cclap::ArgParser ap(argc, argv);

    auto program_name = ap.program_name();
    auto arguments = ap.args();
    auto flags = ap.flags();
    auto switches = ap.switches();

    REQUIRE(program_name == argv[0]);

    //Test by checking if we have flags in regular arguments
    for (auto argument: arguments){
        REQUIRE(argument.front() != '-');
    }
}
