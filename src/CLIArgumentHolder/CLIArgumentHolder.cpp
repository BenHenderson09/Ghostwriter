#include <string>
#include <vector>
#include <map>
#include "../../config/FlagConfig.hpp"
#include "CLIArgumentHolder.hpp"

CLIArgumentHolder::CLIArgumentHolder(const std::string& inputArgs){
    processInputArgs(inputArgs);
}

CLIArgumentHolder::CLIArgumentHolder(char** inputArgs){
    processInputArgs(convertCStringArgsToString(inputArgs));
}

std::string CLIArgumentHolder::getInputArgs() const {
    return inputArgs;
}

void CLIArgumentHolder::processInputArgs(const std::string& inputArgs){
    this->inputArgs = inputArgs;
    clearPreviouslyParsedArgs();
    parseInputArgs();
}

std::string CLIArgumentHolder::getParsedStringArg(const std::string& nameOfStringArg) const {
    return this->parsedStringArgs.at(nameOfStringArg);
}

bool CLIArgumentHolder::getParsedBoolArg(const std::string& nameOfBoolArg) const {
    return this->parsedBoolArgs.at(nameOfBoolArg);
}

bool CLIArgumentHolder::wasArgProvided(const std::string& arg) const {
    return inputArgs.find(arg) != std::string::npos;
}

std::string CLIArgumentHolder::convertCStringArgsToString(char** inputArgs){
    std::string argsAsString;

    // Iterate over all user-defined inputArgs, which begin at index 1
    for (int i{1}; *(inputArgs+i); i++){
        if (i != 1) argsAsString += " ";

        argsAsString += *(inputArgs+i);
    }

    return argsAsString;
}

void CLIArgumentHolder::clearPreviouslyParsedArgs(){
    parsedBoolArgs.clear();
    parsedStringArgs.clear();
}

void CLIArgumentHolder::parseInputArgs(){
    parseBoolArgs();
    parseStringArgs();
    checkIfArgsAreValid();
}

void CLIArgumentHolder::parseBoolArgs(){
    std::vector<std::string> boolFlags{extractFlagsFromConfig("bool")};

    for (const std::string& flag : boolFlags){
        bool isFlagSpecifiedInArgs{inputArgs.find(flag) != std::string::npos};

        if (isFlagSpecifiedInArgs){
            std::pair<std::string, bool> parsedBoolArg(flag, true);

            parsedBoolArgs.insert(parsedBoolArg);
        }
    }
}

void CLIArgumentHolder::parseStringArgs(){
    std::vector<std::string> stringFlags{extractFlagsFromConfig("string")};

    for (const std::string& flag : stringFlags){
        bool isFlagSpecifiedInArgs{inputArgs.find(flag) != std::string::npos};

        if (isFlagSpecifiedInArgs){
            std::pair<std::string, std::string>
                parsedStringArg(flag, extractFlagValueFromArgs(flag));

            parsedStringArgs.insert(parsedStringArg);
        } 
    }
}

std::string CLIArgumentHolder::extractFlagValueFromArgs(const std::string& flag){
    std::size_t indexOfStartOfFlagValue{inputArgs.find(flag) + flag.length() + 1};

    checkIfFlagValueIsPresent(indexOfStartOfFlagValue);

    std::size_t indexOfEndOfFlagValue{inputArgs.find(" --", indexOfStartOfFlagValue)};
    std::size_t lengthOfFlagValue{indexOfEndOfFlagValue - indexOfStartOfFlagValue};

    std::string flagValue{inputArgs.substr(indexOfStartOfFlagValue, lengthOfFlagValue)};

    return flagValue;
}

void CLIArgumentHolder::checkIfFlagValueIsPresent(int indexOfStartOfFlagValue){
    bool flagIsLastAndHasNoValue{indexOfStartOfFlagValue > inputArgs.length()};
    std::string flagLeftBlankMessage{"Specified flag value can't be left blank."};

    if (flagIsLastAndHasNoValue)
        throw std::runtime_error(flagLeftBlankMessage);

    bool flagIsFollowedByAnotherFlag{inputArgs.substr(indexOfStartOfFlagValue, 2) == "--"};

    if (flagIsFollowedByAnotherFlag)
        throw std::runtime_error(flagLeftBlankMessage);
}

std::vector<std::string> CLIArgumentHolder::extractFlagsFromConfig(const std::string& flagType){
    std::vector<std::string> flags;

    for (const auto& item : FlagConfig::FLAG_CONFIGURATIONS.items()){
        std::string typeOfFlagInConfig{FlagConfig::FLAG_CONFIGURATIONS[item.key()]["type"]};
        
        if (typeOfFlagInConfig == flagType) flags.push_back(item.key());
    }

    return flags;
}

void CLIArgumentHolder::checkIfArgsAreValid(){
    checkIfInputTextHasBeenGivenCorrectly();
}

void CLIArgumentHolder::checkIfInputTextHasBeenGivenCorrectly(){
    bool inputFileProvided{wasArgProvided("--input-file")};
    bool inputTextProvided{wasArgProvided("--input-text")};

    if (!inputFileProvided && !inputTextProvided)
        throw std::runtime_error("Input text must be provided.");

    if (inputFileProvided && inputTextProvided)
        throw std::runtime_error("Only one form of input text permitted.");
}
