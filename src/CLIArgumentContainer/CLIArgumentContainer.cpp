#include <iostream>
#include <string>
#include <vector>
#include "CLIArgumentContainer.hpp"

CLIArgumentContainer::CLIArgumentContainer(const std::string& inputArgs){
    processInputArgs(inputArgs);
}

CLIArgumentContainer::CLIArgumentContainer(char** inputArgs){
    processInputArgs(convertDoublePointerArgsToString(inputArgs));
}

std::string CLIArgumentContainer::getInputArgs(){
    return inputArgs;
}

void CLIArgumentContainer::processInputArgs(const std::string& inputArgs){
    this->inputArgs = inputArgs;
    clearPreviouslyParsedArgs();
    parseInputArgs();
}

std::string CLIArgumentContainer::getParsedStringArg(const std::string& nameOfStringArg){
    return this->parsedStringArgs[nameOfStringArg];
}

bool CLIArgumentContainer::getParsedBoolArg(const std::string& nameOfBoolArg){
    return this->parsedBoolArgs[nameOfBoolArg];
}

bool CLIArgumentContainer::wasArgProvided(const std::string& arg){
    return inputArgs.find(arg) != std::string::npos;
}

std::string CLIArgumentContainer::convertDoublePointerArgsToString(char** inputArgs){
    std::string argsAsString;

    // Iterate over all user-defined inputArgs, which begin at index 1
    for (int i = 1; *(inputArgs+i); i++){
        if (i != 1) argsAsString += " ";

        argsAsString += *(inputArgs+i);
    }

    return argsAsString;
}

void CLIArgumentContainer::clearPreviouslyParsedArgs(){
    parsedBoolArgs.clear();
    parsedStringArgs.clear();
}

void CLIArgumentContainer::parseInputArgs(){
    parseBoolArgs();
    parseStringArgs();
    checkIfArgsAreValid();
}

void CLIArgumentContainer::parseBoolArgs(){
    std::vector<std::string> boolFlags = extractFlagsFromConfig("bool");

    for (const std::string& flag : boolFlags){
        bool isFlagSpecifiedInArgs = inputArgs.find(flag) != std::string::npos;

        if (isFlagSpecifiedInArgs){
            std::pair<std::string, bool> parsedBoolArg(flag, true);

            parsedBoolArgs.insert(parsedBoolArg);
        }
    }
}

void CLIArgumentContainer::parseStringArgs(){
    std::vector<std::string> stringFlags = extractFlagsFromConfig("string");

    for (const std::string& flag : stringFlags){
        bool isFlagSpecifiedInArgs = inputArgs.find(flag) != std::string::npos;

        if (isFlagSpecifiedInArgs){
            std::pair<std::string, std::string>
                parsedStringArg(flag, extractFlagValueFromArgs(flag));

            parsedStringArgs.insert(parsedStringArg);
        } 
    }
}

std::string CLIArgumentContainer::extractFlagValueFromArgs(const std::string& flag){
    int indexOfStartOfFlagValue = inputArgs.find(flag) + flag.length() + 1;

    checkIfFlagValueIsPresent(indexOfStartOfFlagValue);

    int indexOfEndOfFlagValue = inputArgs.find(" --", indexOfStartOfFlagValue);
    int lengthOfFlagValue = indexOfEndOfFlagValue - indexOfStartOfFlagValue;

    std::string flagValue = inputArgs.substr(indexOfStartOfFlagValue, lengthOfFlagValue);

    return flagValue;
}

void CLIArgumentContainer::checkIfFlagValueIsPresent(int indexOfStartOfFlagValue){
    bool flagIsLastAndHasNoValue = indexOfStartOfFlagValue > inputArgs.length();
    std::string flagLeftBlankMessage = "Specified flag value can't be left blank.";

    if (flagIsLastAndHasNoValue)
        throw std::runtime_error(flagLeftBlankMessage);

    bool flagIsFollowedByAnotherFlag =
        inputArgs.substr(indexOfStartOfFlagValue, 2) == "--";

    if (flagIsFollowedByAnotherFlag)
        throw std::runtime_error(flagLeftBlankMessage);
}

std::vector<std::string> CLIArgumentContainer::extractFlagsFromConfig(const std::string& flagType){
    std::vector<std::string> flags;

    for (const auto& item : FlagConfig::FLAG_CONFIGURATIONS.items()){
        std::string typeOfFlagInConfig =
            FlagConfig::FLAG_CONFIGURATIONS[item.key()]["type"];
        
        if (typeOfFlagInConfig == flagType) flags.push_back(item.key());
    }

    return flags;
}

void CLIArgumentContainer::checkIfArgsAreValid(){
    checkIfInputTextHasBeenGivenCorrectly();
}

void CLIArgumentContainer::checkIfInputTextHasBeenGivenCorrectly(){
    bool inputFileProvided = wasArgProvided("--input-file");
    bool inputTextProvided = wasArgProvided("--input-text");

    if (!inputFileProvided && !inputTextProvided)
        throw std::runtime_error("Input text must be provided.");

    if (inputFileProvided && inputTextProvided)
        throw std::runtime_error("Only one form of input text permitted.");
}