#include <iostream>
#include <fstream>
#include "OutputWriter.hpp"
#include "../CLIArgumentContainer/CLIArgumentContainer.hpp"

OutputWriter::OutputWriter(CLIArgumentContainer& argumentContainer)
    : argumentContainer(argumentContainer){}

void OutputWriter::writeOutputText(const std::string& outputText){
    bool isOutputLocationAFile = argumentContainer.wasArgProvided("--output-file");

    if (isOutputLocationAFile){
        const std::string& outputFileLocation =
            argumentContainer.getParsedStringArg("--output-file");

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