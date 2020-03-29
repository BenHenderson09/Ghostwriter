#ifndef CLI_ARGUMENT_CONTAINER_HPP
#define CLI_ARGUMENT_CONTAINER_HPP

#include <string>
#include <vector>
#include <map>

class CLIArgumentContainer {
    public:
        CLIArgumentContainer(const std::string& inputArgs);
        CLIArgumentContainer(char** inputArgs);
        CLIArgumentContainer() = default;

        std::string getInputArgs() const;
        void processInputArgs(const std::string& inputArgs);

        std::string getParsedStringArg(const std::string& nameOfStringArg) const;
        bool getParsedBoolArg(const std::string& nameOfBoolArg) const;

        bool wasArgProvided(const std::string& nameOfArg) const;

    private:
        std::string inputArgs;
        std::map<std::string, std::string> parsedStringArgs;
        std::map<std::string, bool> parsedBoolArgs;

        void clearPreviouslyParsedArgs();
        void parseInputArgs();
        std::string convertCStringArgsToString(char** args);
        void parseBoolArgs();
        void parseStringArgs();
        std::string extractFlagValueFromArgs(const std::string& args);
        void checkIfFlagValueIsPresent(int indexOfStartOfFlagValue);
        std::vector<std::string> extractFlagsFromConfig(const std::string& flagType);
        void checkIfArgsAreValid();
        void checkIfInputTextHasBeenGivenCorrectly();
};

#endif
