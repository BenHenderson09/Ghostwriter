#ifndef CLIARGUMENTPARSER_H
#define CLIARGUMENTPARSER_H

#include <map>
#include <string>
#include <vector>
#include "../config/FlagConfig.hpp"

class CLIArgumentParser {
    public:
        CLIArgumentParser(std::string args);
        CLIArgumentParser(char** args);

        std::string args;
        std::map<std::string, std::string> parsedStringArgs;
        std::map<std::string, bool> parsedBoolArgs;

    private:
        void parseArgs();
        std::string convertDoublePointerArgsToString(char** args);
        void parseBoolArgs();
        void parseStringArgs();
        std::string extractFlagValueFromArgs(std::string args);
        std::vector<std::string> extractFlagsFromConfig(std::string type);
};

#endif