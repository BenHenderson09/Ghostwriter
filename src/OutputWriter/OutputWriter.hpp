#ifndef OUTPUTWRITER_HPP
#define OUTPUTWRITER

#include <string>
#include "../CLIArgumentParser/CLIArgumentParser.hpp"

class OutputWriter {
    public:
        OutputWriter(std::string outputText);
        void writeOutputText(CLIArgumentParser argumentParser);

    private:
        std::string outputText;

        void writeToOutputFile(std::string outputFileLocation);
        void writeToConsole();
};

#endif