#include <iostream>
#include "CLIArgumentContainer/CLIArgumentContainer.hpp"
#include "TextParaphraser/TextParaphraser.hpp"
#include "OutputWriter/OutputWriter.hpp"

int main(int argc, char** argv){
    try {
        CLIArgumentContainer argumentContainer(argv);

        TextParaphraser paraphraser(argumentContainer);

        OutputWriter writer(argumentContainer);
        writer.writeOutputText(paraphraser.outputText);
    }
    catch(std::exception& e){
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return 0;
}