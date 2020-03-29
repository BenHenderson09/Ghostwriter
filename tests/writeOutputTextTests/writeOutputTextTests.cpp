#include <string>
#include <catch2/catch.hpp>
#include "../../src/writeOutputText/writeOutputText.hpp"
#include "../util/createDummyCLIArgContainer/createDummyCLIArgContainer.hpp"
#include "../../src/util/readFile/readFile.hpp"

TEST_CASE("Output text is written to file", "[output-text-written-to-file]"){
    std::string outputFilePath = "output.txt";
    std::string outputText = "some text";
    CLIArgumentContainer argumentContainer =
        createDummyCLIArgContainer({"--output-file " + outputFilePath});

    writeOutputText(argumentContainer, outputText);

    REQUIRE_NOTHROW(readFile(outputFilePath));
    REQUIRE(readFile(outputFilePath) == outputText);
}