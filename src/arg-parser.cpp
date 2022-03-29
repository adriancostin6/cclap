#include "arg-parser.h"

#include <stdexcept>

namespace cclap {

ArgParser::ArgParser(int argc, const char *argv[]) {
    int i = 0;
    while (i < argc) {
        uint8_t prefix = arg_prefix_len(argv[i]);
        std::string_view arg { argv[i] };
        arg.remove_prefix(prefix);
        if (!prefix) {
            // Store regular argument
            arguments_.push_back(arg);
            ++i;
            continue;
        }

        int j = i; // keep a copy, in case switches are not found
        // Store the switch 
        if (is_switch(argv, argc, i++)) {
            if (prefix == 1) {
                SwitchPair sp(SwitchType::MULTI, arg);
                switches_.push_back(sp);
                continue;
            }
            SwitchPair sp(SwitchType::SINGLE, arg);
            switches_.push_back(sp);
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
uint8_t ArgParser::arg_prefix_len(const char *argv) {
    if (argv[0] == '-' && argv[1] == '-') {
        return 2;
    } else if (argv[0] == '-') {
        return 1;
    } else {
        return 0;
    }
}

bool ArgParser::is_flag(const char *argv[], int argc, int pos) {
    int current_prefix_len = arg_prefix_len(argv[pos]);
    if (current_prefix_len == 0 || pos + 1 == argc) {
        return false;
    }

    int next_prefix_len = arg_prefix_len(argv[pos + 1]);
    return next_prefix_len == 0 ? true : false;
}

bool ArgParser::is_switch(const char *argv[], int argc, int pos) {
    int current_prefix_len = arg_prefix_len(argv[pos]);
    return current_prefix_len != 0 &&
        !is_flag(argv, argc, pos) ? true: false;
}

ArgVector 
ArgParser::get_flag_args(const char *argv[], int argc, int& pos) {
    ++pos;
    ArgVector flag_args;
    while (pos < argc && arg_prefix_len(argv[pos]) == 0) {
        flag_args.emplace_back(argv[pos]);
        ++pos;
    }
    return flag_args;
}

const NamedPairVector& 
ArgParser::flags() const { return flags_; }

const SwitchPairVector& 
ArgParser::switches() const { return switches_; }

const ArgVector& 
ArgParser::args() const { return arguments_; }

}
