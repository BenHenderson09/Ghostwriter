#include <iostream>
#include <fstream>
#include "OutputWriter.hpp"
#include "../CLIArgumentContainer/CLIArgumentContainer.hpp"

namespace {
    // Variables
    std::string outputText_;

    // Prototypes
    void writeToOutputFile(const std::string& outputFileLocation);
    void writeToConsole();

    // Implementation
    void writeToOutputFile(const std::string& outputFileLocation){
        std::ofstream fileWriter;

        fileWriter.open(outputFileLocation);

        fileWriter << outputText_;

        fileWriter.close();
    }

    void writeToConsole(){
        std::cout << outputText_ << "\n";
    }
}

void OutputWriter::writeOutputText
        (const CLIArgumentContainer& argumentContainer, std::string outputText){
    outputText_ = outputText;
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