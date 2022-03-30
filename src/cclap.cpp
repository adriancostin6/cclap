#include "cclap/cclap.h"

#include <stdexcept>

namespace cclap {

ArgParser::ArgParser(int argc, char *argv[]) {
    // Assign program name
    program_name_ = std::string_view{ argv[0] };

    int i = 1;
    while (i < argc) {
        uint8_t prefix = arg_prefix_len(argv[i]);
        std::string_view arg { argv[i] };
        arg.remove_prefix(prefix);
        if (!prefix) {
            // Store regular (required) argument
            arguments_.push_back(arg);
            ++i;
            continue;
        }

        int j = i; // keep a copy, in case switches are not found
        // Store the switch 
        if (is_switch(argv, argc, i++)) {
            // Deal with multi-switches: -odgsajk
            if(prefix == 1) {
                for (int i = 0; i < arg.size(); ++i) {
                    std::string_view individual_switch = arg.substr(i, 1); 
                    switches_.push_back(individual_switch);
                }
            } else {
                switches_.push_back(arg);
            }
            continue;
        }

        // Store a pair consisting of the flag name and flag arguments
        ArgVector flag_args = get_flag_args(argv, argc, j);
        NamedPair flag_pair(arg, flag_args); 
        flags_.push_back(flag_pair);

        i = j; // restore initial value
    }
}

// Returns the argument prefix length
// Used to determine if string is flag (single/double-dash) or argument
uint8_t ArgParser::arg_prefix_len(char *argv) {
    if (argv[0] == '-' && argv[1] == '-') {
        return 2;
    } else if (argv[0] == '-') {
        return 1;
    } else {
        return 0;
    }
}

bool ArgParser::is_flag(char *argv[], int argc, int pos) {
    int current_prefix_len = arg_prefix_len(argv[pos]);
    if (current_prefix_len == 0 || pos + 1 == argc) {
        return false;
    }

    int next_prefix_len = arg_prefix_len(argv[pos + 1]);
    return next_prefix_len == 0 ? true : false;
}

bool ArgParser::is_switch(char *argv[], int argc, int pos) {
    int current_prefix_len = arg_prefix_len(argv[pos]);
    return current_prefix_len != 0 &&
    !is_flag(argv, argc, pos) ? true: false;
}

ArgVector 
ArgParser::get_flag_args(char *argv[], int argc, int& pos) {
    ++pos;
    ArgVector flag_args;
    while (pos < argc && arg_prefix_len(argv[pos]) == 0) {
        flag_args.emplace_back(argv[pos]);
        ++pos;
    }
    return flag_args;
}

const NamedPairVector& ArgParser::flags() const { return flags_; }

const ArgVector& ArgParser::switches() const { return switches_; }

const ArgVector& ArgParser::args() const { return arguments_; }

const ArgName& ArgParser::program_name() const { return program_name_; }

}
