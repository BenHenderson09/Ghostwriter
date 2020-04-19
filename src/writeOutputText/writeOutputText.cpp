#include <iostream>
#include <fstream>
#include "writeOutputText.hpp"
#include "../CLIArgumentHolder/CLIArgumentHolder.hpp"

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

void writeOutputText
        (const CLIArgumentHolder& arguments, const std::string& outputText){
    outputText_ = outputText;
    bool isOutputLocationAFile = arguments.wasArgProvided("--output-file");

    if (isOutputLocationAFile){
        const std::string& outputFileLocation =
            arguments.getParsedStringArg("--output-file");

        writeToOutputFile(outputFileLocation);
    }
    else {
        writeToConsole();
    }
}