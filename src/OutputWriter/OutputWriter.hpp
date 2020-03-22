#ifndef OUTPUTWRITER_HPP
#define OUTPUTWRITER

#include <string>
#include "../CLIArgumentContainer/CLIArgumentContainer.hpp"

// "Public" items
namespace OutputWriter {
    void writeOutputText(const CLIArgumentContainer& argumentContainer, std::string outputText_);
}

// "Private" items
namespace {
    std::string outputText;

    void writeToOutputFile(const std::string& outputFileLocation);
    void writeToConsole();
}

#endif