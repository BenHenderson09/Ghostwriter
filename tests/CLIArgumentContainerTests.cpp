#include <iostream>
#include <string>
#include "../deps/Catch2/include/catch2/catch.hpp"
#include "../src/CLIArgumentContainer/CLIArgumentContainer.hpp"

CLIArgumentContainer createDummyArgumentContainer(const std::initializer_list<std::string>& args){
    std::string arguments = "--input-text placeholder text"; // Required input placeholder

    for (const std::string& arg : args){
        arguments += " " + arg;
    }

    return CLIArgumentContainer(arguments);
}

TEST_CASE("String args handled", "[string-args-handled]"){
    SECTION("Each given form of input text is handled"){
        std::string argName = GENERATE("--input-text", "--input-file");
        std::string argValue = GENERATE("placeholder text", "placeholder.txt");

        std::string concatenatedInputArg = argName + " " + argValue;

        CLIArgumentContainer argumentContainer(concatenatedInputArg);

        REQUIRE(argumentContainer.getParsedStringArg(argName) == argValue);
    }

    SECTION("Output file is handled"){
        std::string argName = "--output-file";
        std::string argValue = "placeholder.txt";
        std::string concatenatedOutputFileArg = argName + " " + argValue;

        CLIArgumentContainer argumentContainer =
            createDummyArgumentContainer({concatenatedOutputFileArg});

        REQUIRE(argumentContainer.getParsedStringArg(argName) == argValue);
    }
}

TEST_CASE("Bool args handled", "[bool-args-handled]"){
    SECTION("Multiple suggestions option is handled"){
        std::string multipleSuggestionsArg = "--multiple-suggestions";

        CLIArgumentContainer argumentContainer =
            createDummyArgumentContainer({multipleSuggestionsArg});

        REQUIRE(argumentContainer.getParsedBoolArg(multipleSuggestionsArg) == true);
    }
}