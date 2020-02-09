#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "CLIArgumentParser.hpp"
#include "../util/JSONUtils/ObjectHasKey.hpp"

CLIArgumentParser::CLIArgumentParser(std::string args){
    this->args = args;
    parseArgs();
}

CLIArgumentParser::CLIArgumentParser(char** args){
    this->args = convertDoublePointerArgsToString(args);
    parseArgs();
}

std::string CLIArgumentParser::convertDoublePointerArgsToString(char** args){
    std::string argsAsString;

    // Iterate over all user-defined args, which begin at index 1
    for (int i = 1; *(args+i); i++){
        if (i != 1){
            argsAsString += " ";
        }

        argsAsString += *(args+i);
    }

    return argsAsString;
}

void CLIArgumentParser::parseArgs(){
    parseBoolArgs();
    parseStringArgs();
    checkIfArgsAreValid();
}

void CLIArgumentParser::parseBoolArgs(){
    std::vector<std::string> boolFlags = extractFlagsFromConfig("bool");

    for (std::string flag : boolFlags){
        bool isFlagSpecifiedInArgs = args.find(flag) != std::string::npos;

        if (isFlagSpecifiedInArgs){
            std::pair<std::string, bool> parsedBoolArg(flag, true);

            parsedBoolArgs.insert(parsedBoolArg);
        }
    }
}

void CLIArgumentParser::parseStringArgs(){
    std::vector<std::string> stringFlags = extractFlagsFromConfig("string");

    for (std::string flag : stringFlags){
        bool isFlagSpecifiedInArgs = args.find(flag) != std::string::npos;

        if (isFlagSpecifiedInArgs){
            std::pair<std::string, std::string>
                parsedStringArg(flag, extractFlagValueFromArgs(flag));

            parsedStringArgs.insert(parsedStringArg);
        } 
    }
}

std::string CLIArgumentParser::extractFlagValueFromArgs(std::string flag){
    int indexOfStartOfFlagValue = args.find(flag) + flag.length() + 1;

    checkIfFlagValueIsPresent(indexOfStartOfFlagValue);

    // Uses index of next flag, or simply an npos value if no flags remain
    int lengthOfFlagValue =
        args.find(" --", indexOfStartOfFlagValue) - indexOfStartOfFlagValue;

    std::string flagValue =
        args.substr(indexOfStartOfFlagValue, lengthOfFlagValue);

    return flagValue;
}

void CLIArgumentParser::checkIfFlagValueIsPresent(int indexOfStartOfFlagValue){
    bool flagIsLastAndHasNoValue = indexOfStartOfFlagValue > args.length();

    if (flagIsLastAndHasNoValue){
        throw std::runtime_error("Specified flag value can't be left blank.");
    }

    bool flagIsFollowedByAnotherFlag = 
        args.substr(indexOfStartOfFlagValue, 2) == "--";

    if (flagIsFollowedByAnotherFlag){
        throw std::runtime_error("Specified flag value can't be left blank.");
    }
}

std::vector<std::string> CLIArgumentParser
    ::extractFlagsFromConfig(std::string type){
    std::vector<std::string> flags;

    for (auto& item : flagConfigurations.items()){
        if (flagConfigurations[item.key()]["type"] == type){
            flags.push_back(item.key());
        }
    }

    return flags;
}

void CLIArgumentParser::checkIfArgsAreValid(){
    checkIfInputTextHasBeenGivenCorrectly();
}

void CLIArgumentParser::checkIfInputTextHasBeenGivenCorrectly(){
    bool inputFileProvided =
        JSONUtils::objectHasKey(parsedStringArgs, "--input-file");

    bool inputTextProvided =
        JSONUtils::objectHasKey(parsedStringArgs, "--input-text");

    if (!inputFileProvided && !inputTextProvided){
        throw std::runtime_error("Input text must be provided.");
    }

    if (inputFileProvided && inputTextProvided){
        throw std::runtime_error("Only one form of input text permitted.");
    }
}