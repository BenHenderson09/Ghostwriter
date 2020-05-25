#include <iostream>
#include <fstream>
#include "writeOutputText.hpp"
#include "../CLIArgumentHolder/CLIArgumentHolder.hpp"

namespace {
    void writeToOutputFile(const std::string& outputText, const std::string& outputFileLocation);

    void writeToOutputFile(const std::string& outputText, const std::string& outputFileLocation){
        std::ofstream fileWriter;

        fileWriter.open(outputFileLocation);

        fileWriter << outputText;

        fileWriter.close();
    }
}

void writeOutputText(const CLIArgumentHolder& arguments, const std::string& outputText){
    bool isOutputLocationAFile{arguments.wasArgProvided("--output-file")};

    if (isOutputLocationAFile){
        const std::string& outputFileLocation{arguments.getParsedStringArg("--output-file")};

        writeToOutputFile(outputText, outputFileLocation);
    }
    else {
        std::cout << outputText << "\n";
    }
}