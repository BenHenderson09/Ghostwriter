#include <string>
#include <catch2/catch.hpp>
#include "../../src/CLIArgumentContainer/CLIArgumentContainer.hpp"
#include "../util/createDummyCLIArgContainer/createDummyCLIArgContainer.hpp"

TEST_CASE("Options for setting CLI args function the same way", "[args-set-the-same-way]"){
    std::string placeholderInputArgName = "--input-text";
    std::string placeholderInputArgValue = "placeholder text";
    std::string assembledPlaceholderInputArg =
        placeholderInputArgName + " " + placeholderInputArgValue;

    SECTION("Each method of construction functions the same way"){
        CLIArgumentContainer containerWithStringArgs(assembledPlaceholderInputArg);
        CLIArgumentContainer containerWithCStringArgs(assembledPlaceholderInputArg.c_str());

        bool argsAreParsedTheSameWay =
            containerWithStringArgs.getParsedStringArg(placeholderInputArgName) ==
            containerWithCStringArgs.getParsedStringArg(placeholderInputArgName);

        REQUIRE(argsAreParsedTheSameWay);
    }

    SECTION("Setting CLI args via method functions the same way as constructors"){
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
    SECTION("Each type of input text arg is handled"){
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
            createDummyCLIArgContainer({assembledOutputFileArg});

        REQUIRE(argumentContainer.getParsedStringArg(argName) == argValue);
    }
}

TEST_CASE("Bool args handled", "[bool-args-handled]"){
    SECTION("Multiple suggestions option is handled"){
        std::string multipleSuggestionsArg = "--multiple-suggestions";

        CLIArgumentContainer argumentContainer =
            createDummyCLIArgContainer({multipleSuggestionsArg});

        REQUIRE(argumentContainer.getParsedBoolArg(multipleSuggestionsArg) == true);
    }
}

TEST_CASE("Can determine if CLI arg was provided", "[can-determine-if-arg-provided]"){
    std::string argName = "--multiple-suggestions";
    CLIArgumentContainer argumentContainer =
        createDummyCLIArgContainer({argName});

    REQUIRE(argumentContainer.wasArgProvided(argName) == true);
}