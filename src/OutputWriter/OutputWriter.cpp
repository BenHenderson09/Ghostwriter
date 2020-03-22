#include <iostream>
#include <fstream>
#include "OutputWriter.hpp"
#include "../CLIArgumentContainer/CLIArgumentContainer.hpp"

void OutputWriter::writeOutputText
        (const CLIArgumentContainer& argumentContainer, std::string outputText_){
    outputText = outputText_;
    bool isOutputLocationAFile = argumentContainer.wasArgProvided("--output-file");

    if (isOutputLocationAFile){
        const std::string& outputFileLocation =
            argumentContainer.getParsedStringArg("--output-file");

        writeToOutputFile(outputFileLocation);
    }
    else {
        writeToConsole();
    }
}

namespace {
    void writeToOutputFile(const std::string& outputFileLocation){
        std::ofstream fileWriter;

        fileWriter.open(outputFileLocation);

        fileWriter << outputText;

        fileWriter.close();
    }

    void writeToConsole(){
        std::cout << outputText << "\n";
    }
}