#include <string>
#include <fstream>
#include <vector>
#include <catch2/catch.hpp>
#include "../../src/paraphraseText/paraphraseText.hpp"
#include "../../src/CLIArgumentHolder/CLIArgumentHolder.hpp"
#include "../util/createDummyCLIArgHolder/createDummyCLIArgHolder.hpp"
#include "../../src/util/readFile/readFile.hpp"

std::vector<std::string> splitTextIntoEachSetOfSuggestions(std::string text){
    std::vector<std::string> sections;

    for (std::size_t startIndex{text.find("(")};
            startIndex != std::string::npos;
            startIndex = text.find("(")){
        std::size_t endIndex{text.find(")")};
        std::size_t lengthOfSetOfSuggestions{endIndex - startIndex + 1};
        
        std::string setOfSuggestions{text.substr(startIndex, lengthOfSetOfSuggestions)};
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
        std::string argName{"--input-text"};
        std::string argValue{"placeholder text"};
        std::string assembledInputArg{argName + " " + argValue};

        CLIArgumentHolder arguments(assembledInputArg);
        std::string paraphrasedText{paraphraseText(arguments)};

        REQUIRE_FALSE(paraphrasedText == argValue);
    }

    SECTION("--input-file is paraphrased"){
        std::string placeholderInputFilePath{"placeholder_input"};
        setupPlaceholderInputFile(placeholderInputFilePath);    

        CLIArgumentHolder arguments("--input-file " + placeholderInputFilePath);
        std::string paraphrasedText{paraphraseText(arguments)};

        REQUIRE_FALSE(paraphrasedText == readFile(placeholderInputFilePath));
    }
}

TEST_CASE("Multiple paraphrasing suggestions are provided", "[multiple-suggestions-provided]"){
    CLIArgumentHolder arguments{createDummyCLIArgHolder({"--multiple-suggestions"})};

    std::string paraphrasedText{paraphraseText(arguments)};
    
    for (std::string setOfSuggestions : splitTextIntoEachSetOfSuggestions(paraphrasedText)){
        bool setOfSuggestionsHasMultipleSuggestions{
            setOfSuggestions.find("/") != std::string::npos
        };

        REQUIRE(setOfSuggestionsHasMultipleSuggestions);
    }
} 