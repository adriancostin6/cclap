#include <string>

#include <catch2/catch_test_macros.hpp>

#include "arg-parser.h"

// Chose to provide mandatory arguments first, check for correct order
TEST_CASE("Arguments in the right order (options last)", "[arg-parser]") {
    int argc = 12;
    const char *argv[] = {
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

    auto arguments = ap.args();
    auto flags = ap.flags();
    auto switches = ap.switches();

    // test size of returned arguments
    REQUIRE(arguments.size() == 3);
    REQUIRE(flags.size() == 2);
    REQUIRE(switches.size() == 4);

    // test for argument equality
    for (int i = 0; i < arguments.size(); ++i) {
        REQUIRE (arguments[i] == argv[i]);
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

    auto switch1 = switches[0].second;
    REQUIRE(switch1 == "single-switch");
    auto switch_type1 = switches[0].first;
    REQUIRE(switch_type1 == cclap::SwitchType::SINGLE);

    auto switch2 = switches[1].second;
    REQUIRE(switch2 == "s");
    auto switch_type2 = switches[1].first;
    REQUIRE(switch_type2 == cclap::SwitchType::SINGLE);

    auto switch3 = switches[2].second;
    REQUIRE(switch3 == "multi-switch-next");
    auto switch_type3 = switches[2].first;
    REQUIRE(switch_type3 == cclap::SwitchType::SINGLE);

    auto switch4 = switches[3].second;
    REQUIRE(switch4 == "src");
    auto switch_type4 = switches[3].first;
    REQUIRE(switch_type4 == cclap::SwitchType::MULTI);
} 

// Chose to provide mandatory arguments first, check for wrong order
TEST_CASE("Arguments in the wrong order (options first)", "[arg-parser]") {
    int argc = 12;
    const char *argv[] = {
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

    auto arguments = ap.args();
    auto flags = ap.flags();
    auto switches = ap.switches();

    //Test by checking if we have flags in regular arguments
    for (auto argument: arguments){
        REQUIRE(argument.front() != '-');
    }
}
