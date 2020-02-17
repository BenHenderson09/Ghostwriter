#include <iostream>
#include <fstream>
#include "OutputWriter.hpp"
#include "../CLIArgumentParser/CLIArgumentParser.hpp"
#include "../util/JSONUtils/ObjectHasKey.hpp"

OutputWriter::OutputWriter(const CLIArgumentParser& argumentParser)
    : argumentParser(argumentParser){}

void OutputWriter::writeOutputText(const std::string& outputText){
    bool isOutputLocationAFile = JSONUtils::objectHasKey(
        argumentParser.parsedStringArgs,
        "--output-file"
    );

    if (isOutputLocationAFile){
        const std::string& outputFileLocation =
            argumentParser.parsedStringArgs.at("--output-file");

        writeToOutputFile(outputFileLocation, outputText);
    }
    else {
        writeToConsole(outputText);
    }
}

void OutputWriter::writeToOutputFile
    (const std::string& outputFileLocation, const std::string& outputText){
    std::ofstream fileWriter;
    fileWriter.open(outputFileLocation);
    fileWriter << outputText;
    fileWriter.close();
}

void OutputWriter::writeToConsole(const std::string& outputText){
    std::cout << outputText << "\n";
}