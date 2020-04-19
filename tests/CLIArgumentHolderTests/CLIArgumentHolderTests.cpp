#include <string>
#include <catch2/catch.hpp>
#include "../../src/CLIArgumentHolder/CLIArgumentHolder.hpp"
#include "../util/createDummyCLIArgHolder/createDummyCLIArgHolder.hpp"

TEST_CASE("Options for setting CLI args function the same way", "[args-set-the-same-way]"){
    std::string placeholderInputArgName = "--input-text";
    std::string placeholderInputArgValue = "placeholder text";
    std::string assembledPlaceholderInputArg =
        placeholderInputArgName + " " + placeholderInputArgValue;

    SECTION("Each method of construction functions the same way"){
        CLIArgumentHolder holderWithStringArgs(assembledPlaceholderInputArg);
        CLIArgumentHolder holderWithCStringArgs(assembledPlaceholderInputArg.c_str());

        bool argsAreParsedTheSameWay =
            holderWithStringArgs.getParsedStringArg(placeholderInputArgName) ==
            holderWithCStringArgs.getParsedStringArg(placeholderInputArgName);

        REQUIRE(argsAreParsedTheSameWay);
    }

    SECTION("Setting CLI args via method functions the same way as constructors"){
        CLIArgumentHolder holderWithConstructorArgs(assembledPlaceholderInputArg);
        CLIArgumentHolder holderWithMethodArgs;
        holderWithMethodArgs.processInputArgs(assembledPlaceholderInputArg);

        bool argsAreParsedTheSameWay =
            holderWithConstructorArgs.getParsedStringArg(placeholderInputArgName) ==
            holderWithMethodArgs.getParsedStringArg(placeholderInputArgName);

        REQUIRE(argsAreParsedTheSameWay);
    }
}

TEST_CASE("String args handled", "[string-args-handled]"){
    SECTION("Each type of input text arg is handled"){
        std::string argName = GENERATE("--input-text", "--input-file");
        std::string argValue = GENERATE("placeholder text", "placeholder.txt");
        std::string assembledInputArg = argName + " " + argValue;

        CLIArgumentHolder arguments(assembledInputArg);

        REQUIRE(arguments.getParsedStringArg(argName) == argValue);
    }

    SECTION("Output file is handled"){
        std::string argName = "--output-file";
        std::string argValue = "placeholder.txt";
        std::string assembledOutputFileArg = argName + " " + argValue;

        CLIArgumentHolder arguments =
            createDummyCLIArgHolder({assembledOutputFileArg});

        REQUIRE(arguments.getParsedStringArg(argName) == argValue);
    }
}

TEST_CASE("Bool args handled", "[bool-args-handled]"){
    SECTION("Multiple suggestions option is handled"){
        std::string multipleSuggestionsArg = "--multiple-suggestions";

        CLIArgumentHolder arguments =
            createDummyCLIArgHolder({multipleSuggestionsArg});

        REQUIRE(arguments.getParsedBoolArg(multipleSuggestionsArg) == true);
    }
}

TEST_CASE("Can determine if CLI arg was provided", "[can-determine-if-arg-provided]"){
    std::string argName = "--multiple-suggestions";
    CLIArgumentHolder arguments =
        createDummyCLIArgHolder({argName});

    REQUIRE(arguments.wasArgProvided(argName) == true);
}