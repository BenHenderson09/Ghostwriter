#ifndef OUTPUTWRITER_HPP
#define OUTPUTWRITER

#include <string>
#include "../CLIArgumentContainer/CLIArgumentContainer.hpp"

class OutputWriter {
    public:
        OutputWriter(CLIArgumentContainer& argumentContainer);
        void writeOutputText(const std::string& outputText);

    private:
        CLIArgumentContainer& argumentContainer;

        void writeToOutputFile(
            const std::string& outputFileLocation,
            const std::string& outputText
        );
        
        void writeToConsole(const std::string& outputText);
};

#endif