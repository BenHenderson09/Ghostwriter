#ifndef CLIARGUMENTPARSER_HPP
#define CLIARGUMENTPARSER_HPP

#include <map>
#include <string>
#include <vector>
#include "../config/FlagConfig.hpp"

class CLIArgumentParser {
    public:
        CLIArgumentParser(const std::string& args);
        CLIArgumentParser(char** args);
        CLIArgumentParser() = default;

        std::string getArgs();
        void setArgs(const std::string& args);

        std::map<std::string, std::string> parsedStringArgs;
        std::map<std::string, bool> parsedBoolArgs;

    private:
        std::string args;

        void clearPreviouslyParsedArgs();
        void parseArgs();
        std::string convertDoublePointerArgsToString(char** args);
        void parseBoolArgs();
        void parseStringArgs();
        std::string extractFlagValueFromArgs(const std::string& args);
        void checkIfFlagValueIsPresent(int indexOfStartOfFlagValue);
        std::vector<std::string>
            extractFlagsFromConfig(const std::string& type);
        void checkIfArgsAreValid();
        void checkIfInputTextHasBeenGivenCorrectly();
};

#endif
