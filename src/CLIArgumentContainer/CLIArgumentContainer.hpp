#ifndef CLIARGUMENTCONTAINER_HPP
#define CLIARGUMENTCONTAINER_HPP

#include <map>
#include <string>
#include <vector>
#include "../config/FlagConfig.hpp"

class CLIArgumentContainer {
    public:
        CLIArgumentContainer(const std::string& args);
        CLIArgumentContainer(char** args);

        std::string getInputArgs();
        void processInputArgs(const std::string& args);

        std::string getParsedStringArg(const std::string& nameOfStringArg);
        bool getParsedBoolArg(const std::string& nameOfBoolArg);

        bool wasArgProvided(const std::string& nameOfArg);

    private:
        std::string inputArgs;
        std::map<std::string, std::string> parsedStringArgs;
        std::map<std::string, bool> parsedBoolArgs;

        void clearPreviouslyParsedArgs();
        void parseInputArgs();
        std::string convertDoublePointerArgsToString(char** args);
        void parseBoolArgs();
        void parseStringArgs();
        std::string extractFlagValueFromArgs(const std::string& args);
        void checkIfFlagValueIsPresent(int indexOfStartOfFlagValue);
        std::vector<std::string> extractFlagsFromConfig(const std::string& flagType);
        void checkIfArgsAreValid();
        void checkIfInputTextHasBeenGivenCorrectly();
};

#endif
