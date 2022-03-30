#ifndef CCLAP_H
#define CCLAP_H

#include <string_view>
#include <vector>
#include <utility>

namespace cclap {
    typedef std::string_view ArgName;
    typedef std::vector<ArgName> ArgVector;
    typedef std::pair<ArgName, ArgVector> NamedPair;
    typedef std::vector<NamedPair> NamedPairVector;

/** @brief Command Line Argument Parser class.
*
*   Takes a string of command line arguments, processes them and stores them,
*   separating into required and optional arguments.
*   @note 
*   Optional arguments are split into flags and switches, the difference
*   being that flags can accept extra input arguments as opposed to switches.
*
*   Example usage:
*   @code 
*   ArgParser ap("hello world -i ~/infile1.txt ~/infile2.txt -o ~/outfile.txt" --read-one-line -rol)
*
*   auto required_args = ap.args();
*   auto flags = ap.flags();
*   auto switches = ap.switches();
*
*   // Accessing regular, required arguments
*   for (auto arg: required_args) {
*       std::cout << arg << std::endl;
*   }
*
*   // Accessing flags
*   for (auto flag: flags) {
*       std::cout << "Flag:" << flag.first << " Value: "<< flag.second << std::endl;
*   }
*
*   // Accessing switches
*   for (auto switch_pair: switches) {
*       //Single switches
*       if (switch_pair.first == cclap::SwitchType::SINGLE) {
*           std::cout << "Single switches: ";
*           for (auto switch: switch_pair.second) {
*              std::cout << switch << " "; 
*           }
*           std::cout << std::endl;
*       }
*
*       //Multi switches
*       if (switch_pair.first == cclap::SwitchType::MULTI) {
*           std::cout << "Multi switch: " << switch_pair.second;
*       }
*   }
*   @endcode
*
*   @author Adrian Costin <adriancostin6@gmail.com>
*   @date 28 March, 2022
*/
class ArgParser {
public:
    /// Constructor. Processes input command line arguments into member data
    ArgParser(int argc, const char *argv[]);

    const std::string_view& program_name() const;
    /// @returns vector of pairs: ["flag-name": [flag value ...]]
    const NamedPairVector& flags() const;
    /// @returns vector of pairs: [SwitchType: "switch-name" ...]
    const ArgVector& switches() const;
    /// @returns vector of arguments: [arg ...]
    const ArgVector& args() const;

private:
    ArgVector get_flag_args(const char *argv[], int argc, int& pos);
    uint8_t arg_prefix_len(const char *arg);
    bool is_flag(const char *argv[], int argc, int pos);
    bool is_switch(const char *argv[], int argc, int pos);

    std::string_view program_name_;
    NamedPairVector flags_;
    ArgVector switches_;
    ArgVector arguments_;

};

}

#endif // ARG_PARSER_H
