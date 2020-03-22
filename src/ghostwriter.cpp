#include <iostream>
#include "CLIArgumentContainer/CLIArgumentContainer.hpp"
#include "TextParaphraser/TextParaphraser.hpp"
#include "OutputWriter/OutputWriter.hpp"

int main(int argc, char** argv){
    try {
        CLIArgumentContainer argumentContainer(argv);
        std::string outputText = TextParaphraser::paraphraseText(argumentContainer);

        OutputWriter::writeOutputText(argumentContainer, outputText);
    }
    catch(std::exception& e){
        std::cerr << e.what() << "\n";

        return EXIT_FAILURE;
    }

    return 0;
}