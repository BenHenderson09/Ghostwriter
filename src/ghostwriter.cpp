#include <iostream>
#include "CLIArgumentHolder/CLIArgumentHolder.hpp"
#include "paraphraseText/paraphraseText.hpp"
#include "writeOutputText/writeOutputText.hpp"

int main(int argc, char** argv){
    try {
        CLIArgumentHolder arguments(argv);
        std::string outputText{paraphraseText(arguments)};

        writeOutputText(arguments, outputText);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << "\n";

        return EXIT_FAILURE;
    }

    return 0;
}