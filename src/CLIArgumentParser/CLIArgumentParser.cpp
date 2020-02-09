#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "CLIArgumentParser.hpp"

// TODO implement a way of checking for invalid args

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
    int indexOfStartOfFlagValue =
        args.find(flag) + flag.length() + 1;

    // Uses index of next flag, or simply an npos value if no flags remain
    int lengthOfFlagValue =
        args.find(" --", indexOfStartOfFlagValue) - indexOfStartOfFlagValue;

    std::string flagValue =
        args.substr(indexOfStartOfFlagValue, lengthOfFlagValue);

    return flagValue;
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