#ifndef CCLAP_H
#define CCLAP_H

#include <string_view>
#include <optional>
#include <functional>
#include <vector>
#include <utility>

namespace cclap {
    typedef std::string_view ArgName;
    typedef std::vector<ArgName> ArgVector;
    typedef std::pair<ArgName, ArgVector> NamedPair;
    typedef std::vector<NamedPair> NamedPairVector;

/** @brief Command Line Argument Parser class.
*
*   Processes and stores command line arguments separating into flags, switches
*   and other arguments.
*
*   @author Adrian Costin <adriancostin6@gmail.com>
*   @date 28 March, 2022
*/
class ArgParser {
public:
    ArgParser() = delete;

    /**
     * @brief Constructor. 
     *
     * Process and store command line arguments.
     * @returns ArgParser object containing arguments, grouped by type
     * */
    ArgParser(int argc, char *argv[]);

    const ArgName& program_name() const;

    /**
     * @brief Getter for flag type arguments.
     *
     * Flags contain arguments that are associated with them.
     * Example: -i file --output file
     * @returns vector of flag pairs: ["flag-name": [flag value ...] ...]
     * */
    const NamedPairVector& flags() const;

    /**
     * @brief Getter for switch type arguments.
     *
     * Switches are flags that do not have values associated with them.
     * Example: -uno --skip-intro -h
     * @returns vector of switches: ["switch-name" ...]
     * */
    const ArgVector& switches() const;

    /**
     * @brief Getter for other arguments.
     * @returns vector of arguments: [arg ...]
     * */
    const ArgVector& args() const;

    /** 
     * @param[in]  flag_name Name of flag to search, without dashes
     * @returns optional containing the flag value if present
     * */
    std::optional<const ArgVector>
    find_flag(std::string_view flag_name) const; 

    bool find_switch(std::string_view switch_name) const;
    

private:
    ArgVector get_flag_args(char *argv[], int argc, int& pos);
    uint8_t arg_prefix_len(char *arg);
    bool is_flag(char *argv[], int argc, int pos);
    bool is_switch(char *argv[], int argc, int pos);

    ArgName program_name_;
    NamedPairVector flags_;
    ArgVector switches_;
    ArgVector arguments_;

};

}

#endif // ARG_PARSER_H
