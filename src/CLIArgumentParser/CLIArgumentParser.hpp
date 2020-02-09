#ifndef CLIARGUMENTPARSER_HPP
#define CLIARGUMENTPARSER_HPP

#include <map>
#include <string>
#include <vector>
#include "../config/FlagConfig.hpp"

class CLIArgumentParser {
    public:
        CLIArgumentParser(std::string args);
        CLIArgumentParser(char** args);
        CLIArgumentParser() = default;

        std::string args;
        std::map<std::string, std::string> parsedStringArgs;
        std::map<std::string, bool> parsedBoolArgs;

    private:
        void parseArgs();
        std::string convertDoublePointerArgsToString(char** args);
        void parseBoolArgs();
        void parseStringArgs();
        std::string extractFlagValueFromArgs(std::string args);
        void checkIfFlagValueIsPresent(int indexOfStartOfFlagValue);
        std::vector<std::string> extractFlagsFromConfig(std::string type);
        void checkIfArgsAreValid();
        void checkIfInputTextHasBeenGivenCorrectly();
};

#endif