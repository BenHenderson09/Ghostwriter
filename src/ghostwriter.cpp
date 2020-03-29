#include <iostream>
#include "CLIArgumentContainer/CLIArgumentContainer.hpp"
#include "paraphraseText/paraphraseText.hpp"
#include "writeOutputText/writeOutputText.hpp"

int main(int argc, char** argv){
    try {
        CLIArgumentContainer argumentContainer(argv);
        std::string outputText = paraphraseText(argumentContainer);

        writeOutputText(argumentContainer, outputText);
    }
    catch(std::exception& e){
        std::cerr << e.what() << "\n";

        return EXIT_FAILURE;
    }

    return 0;
}