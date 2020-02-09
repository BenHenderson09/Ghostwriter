#include <iostream>
#include "CLIArgumentParser/CLIArgumentParser.hpp"
#include "TextParaphraser/TextParaphraser.hpp"
#include "OutputWriter/OutputWriter.hpp"
#include "./util/JSONUtils/ObjectHasKey.hpp"

int main(int argc, char** argv){
    CLIArgumentParser argumentParser(argv);
    TextParaphraser paraphraser(argumentParser);

    OutputWriter writer(paraphraser.outputText);
    writer.writeOutputText(argumentParser);

    return 0;
}