#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <catch2/catch.hpp>
#include "../../src/TextParaphraser/TextParaphraser.hpp"
#include "../../src/CLIArgumentContainer/CLIArgumentContainer.hpp"
#include "../util/createDummyCLIArgContainer/createDummyCLIArgContainer.hpp"
#include "../../src/util/readFile/readFile.hpp"

std::vector<std::string> splitTextIntoEachSetOfSuggestions(std::string text){
    std::vector<std::string> sections;

    for (int startIndex = text.find("(");
            startIndex != std::string::npos;
            startIndex = text.find("(")){
        int endIndex = text.find(")");
        int lengthOfSetOfSuggestions = endIndex - startIndex + 1;
        
        std::string setOfSuggestions = text.substr(startIndex, lengthOfSetOfSuggestions);
        sections.push_back(setOfSuggestions);

        text.erase(startIndex, lengthOfSetOfSuggestions);
    }

    return sections;
}

void setupPlaceholderInputFile(const std::string& placeholderInputFilePath){
    std::ofstream fileWriter;
    fileWriter.open(placeholderInputFilePath);
    fileWriter << "placeholder text";
    fileWriter.close();
}

TEST_CASE("Each form of input text is paraphrased", "[input-text-paraphrased]"){
    SECTION("--input-text is paraphrased"){
        std::string argName = "--input-text";
        std::string argValue = "placeholder text";
        std::string assembledInputArg = argName + " " + argValue;

        CLIArgumentContainer argumentContainer(assembledInputArg);
        std::string paraphrasedText = TextParaphraser::paraphraseText(argumentContainer);

        REQUIRE_FALSE(paraphrasedText == argValue);
    }

    SECTION("--input-file is paraphrased"){
        std::string placeholderInputFilePath = "placeholder_input";
        setupPlaceholderInputFile(placeholderInputFilePath);    

        CLIArgumentContainer argumentContainer("--input-file " + placeholderInputFilePath);
        std::string paraphrasedText = TextParaphraser::paraphraseText(argumentContainer);

        REQUIRE_FALSE(paraphrasedText == readFile(placeholderInputFilePath));
    }
}

TEST_CASE("Multiple paraphrasing suggestions are provided", "[multiple-suggestions-provided]"){
    CLIArgumentContainer argumentContainer =
        createDummyCLIArgContainer({"--multiple-suggestions"});

    std::string paraphrasedText = TextParaphraser::paraphraseText(argumentContainer);
    
    for (std::string setOfSuggestions : splitTextIntoEachSetOfSuggestions(paraphrasedText)){
        bool setOfSuggestionsHasMultipleSuggestions =
            setOfSuggestions.find("/") != std::string::npos;

        REQUIRE(setOfSuggestionsHasMultipleSuggestions);
    }
} 