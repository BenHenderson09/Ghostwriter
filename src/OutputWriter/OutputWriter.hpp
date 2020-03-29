#ifndef OUTPUT_WRITER_HPP
#define OUTPUT_WRITER_HPP

#include <string>
#include "../CLIArgumentContainer/CLIArgumentContainer.hpp"

namespace OutputWriter {
    void writeOutputText(const CLIArgumentContainer& argumentContainer, std::string outputText);
}

#endif