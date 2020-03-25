#include <iostream>
#include <string>
#include "../deps/Catch2/include/catch2/catch.hpp"
#include "../src/CLIArgumentContainer/CLIArgumentContainer.hpp"

// Required input placeholder
std::string placeholderInputArgName = "--input-text";
std::string placeholderInputArgValue = "placeholder text";
std::string assembledPlaceholderInputArg =
    placeholderInputArgName + " " + placeholderInputArgValue;

CLIArgumentContainer createDummyArgumentContainer
        (const std::initializer_list<std::string>& args = {}){
    std::string dummyArgs;
    dummyArgs += assembledPlaceholderInputArg;

    for (const std::string& arg : args){
        dummyArgs += " " + arg;
    }

    return CLIArgumentContainer(dummyArgs);
}

TEST_CASE("Options for setting CLI args function the same way", "[args-set-the-same-way]"){
    SECTION("Each method of construction functions the same way"){
        CLIArgumentContainer containerWithStringArgs(assembledPlaceholderInputArg);
        CLIArgumentContainer containerWithCStringArgs(assembledPlaceholderInputArg.c_str());

        bool argsAreParsedTheSameWay =
            containerWithStringArgs.getParsedStringArg(placeholderInputArgName) ==
            containerWithCStringArgs.getParsedStringArg(placeholderInputArgName);

        REQUIRE(argsAreParsedTheSameWay);
    }

    SECTION("Setting CLI args via a method functions the same way as constructors"){
        CLIArgumentContainer containerWithConstructorArgs(assembledPlaceholderInputArg);
        CLIArgumentContainer containerWithMethodArgs;
        containerWithMethodArgs.processInputArgs(assembledPlaceholderInputArg);

        bool argsAreParsedTheSameWay =
            containerWithConstructorArgs.getParsedStringArg(placeholderInputArgName) ==
            containerWithMethodArgs.getParsedStringArg(placeholderInputArgName);

        REQUIRE(argsAreParsedTheSameWay);
    }
}

TEST_CASE("String args handled", "[string-args-handled]"){
    SECTION("Each given form of input text is handled"){
        std::string argName = GENERATE("--input-text", "--input-file");
        std::string argValue = GENERATE("placeholder text", "placeholder.txt");
        std::string assembledInputArg = argName + " " + argValue;

        CLIArgumentContainer argumentContainer(assembledInputArg);

        REQUIRE(argumentContainer.getParsedStringArg(argName) == argValue);
    }

    SECTION("Output file is handled"){
        std::string argName = "--output-file";
        std::string argValue = "placeholder.txt";
        std::string assembledOutputFileArg = argName + " " + argValue;

        CLIArgumentContainer argumentContainer =
            createDummyArgumentContainer({assembledOutputFileArg});

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

TEST_CASE("Can determine if CLI a arg was provided", "[can-determine-if-arg-provided]"){
    CLIArgumentContainer argumentContainer = createDummyArgumentContainer();

    REQUIRE(argumentContainer.wasArgProvided(placeholderInputArgName) == true);
}