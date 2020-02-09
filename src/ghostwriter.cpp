#include <iostream>
#include "CLIArgumentParser/CLIArgumentParser.hpp"
#include "TextParaphraser/TextParaphraser.hpp"
#include "OutputWriter/OutputWriter.hpp"
#include "./util/JSONUtils/ObjectHasKey.hpp"

int main(int argc, char** argv){
    try {
        CLIArgumentParser argumentParser(argv);
        TextParaphraser paraphraser(argumentParser);

        OutputWriter writer(paraphraser.outputText);
        writer.writeOutputText(argumentParser);
    }
    catch(std::exception& e){
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return 0;
}