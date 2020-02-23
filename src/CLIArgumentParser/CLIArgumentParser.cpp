#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "CLIArgumentParser.hpp"
#include "../util/JSONUtils/ObjectHasKey.hpp"

CLIArgumentParser::CLIArgumentParser(const std::string& args){
    setArgs(args);
}

CLIArgumentParser::CLIArgumentParser(char** args){
    setArgs(convertDoublePointerArgsToString(args));
}

std::string CLIArgumentParser::getArgs(){
    return args;
}

void CLIArgumentParser::setArgs(const std::string& args){
    this->args = args;
    clearPreviouslyParsedArgs();
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

void CLIArgumentParser::clearPreviouslyParsedArgs(){
    parsedBoolArgs.clear();
    parsedStringArgs.clear();
}

void CLIArgumentParser::parseArgs(){
    parseBoolArgs();
    parseStringArgs();
    checkIfArgsAreValid();
}

void CLIArgumentParser::parseBoolArgs(){
    std::vector<std::string> boolFlags = extractFlagsFromConfig("bool");

    for (const std::string& flag : boolFlags){
        bool isFlagSpecifiedInArgs = args.find(flag) != std::string::npos;

        if (isFlagSpecifiedInArgs){
            std::pair<std::string, bool> parsedBoolArg(flag, true);

            parsedBoolArgs.insert(parsedBoolArg);
        }
    }
}

void CLIArgumentParser::parseStringArgs(){
    std::vector<std::string> stringFlags = extractFlagsFromConfig("string");

    for (const std::string& flag : stringFlags){
        bool isFlagSpecifiedInArgs = args.find(flag) != std::string::npos;

        if (isFlagSpecifiedInArgs){
            std::pair<std::string, std::string>
                parsedStringArg(flag, extractFlagValueFromArgs(flag));

            parsedStringArgs.insert(parsedStringArg);
        } 
    }
}

std::string CLIArgumentParser::extractFlagValueFromArgs(const std::string& flag){
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
    ::extractFlagsFromConfig(const std::string& type){
    std::vector<std::string> flags;

    for (const auto& item : FlagConfig::FLAG_CONFIGURATIONS.items()){
        if (FlagConfig::FLAG_CONFIGURATIONS[item.key()]["type"] == type){
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
