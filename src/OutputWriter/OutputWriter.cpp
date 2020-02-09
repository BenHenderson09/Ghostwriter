#include <iostream>
#include <fstream>
#include "OutputWriter.hpp"
#include "../CLIArgumentParser/CLIArgumentParser.hpp"
#include "../util/JSONUtils/ObjectHasKey.hpp"

OutputWriter::OutputWriter(std::string outputText){
    this->outputText = outputText;
}

void OutputWriter::writeOutputText(CLIArgumentParser argumentParser){
    bool isOutputLocationAFile = JSONUtils::objectHasKey(
        argumentParser.parsedStringArgs,
        "--output-file"
    );

    if (isOutputLocationAFile){
        writeToOutputFile(argumentParser.parsedStringArgs["--output-file"]);
    }
    else {
        writeToConsole();
    }
}

void OutputWriter::writeToOutputFile(std::string outputFileLocation){
    std::ofstream fileWriter;
    fileWriter.open(outputFileLocation);
    fileWriter << outputText;
    fileWriter.close();
}

void OutputWriter::writeToConsole(){
    std::cout << outputText << "\n";
}