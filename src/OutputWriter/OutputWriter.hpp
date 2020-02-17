#ifndef OUTPUTWRITER_HPP
#define OUTPUTWRITER

#include <string>
#include "../CLIArgumentParser/CLIArgumentParser.hpp"

class OutputWriter {
    public:
        OutputWriter(const CLIArgumentParser& argumentParser);
        void writeOutputText(const std::string& outputText);

    private:
        const CLIArgumentParser& argumentParser;

        void writeToOutputFile(
            const std::string& outputFileLocation,
            const std::string& outputText
        );
        
        void writeToConsole(const std::string& outputText);
};

#endif