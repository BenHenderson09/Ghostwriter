#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <curl/curl.h>
#include "TextParaphraser.hpp"
#include "../CLIArgumentParser/CLIArgumentParser.hpp"
#include "../SynonymFinder/SynonymFinder.hpp"
#include "../util/JSONUtils/ObjectHasKey.hpp"

TextParaphraser::TextParaphraser(const CLIArgumentParser& argumentParser)
    : argumentParser(argumentParser){
    organizeInputText();
    paraphraseText();
}

void TextParaphraser::organizeInputText(){
    bool isInputTextProvidedAsArgument = JSONUtils::objectHasKey(
        argumentParser.parsedStringArgs,
        "--input-text"
    );

    if (isInputTextProvidedAsArgument){
        inputText =
            argumentParser.parsedStringArgs.at("--input-text");
    }
    else {
        std::string inputFilePath =
            argumentParser.parsedStringArgs.at("--input-file");

        inputText = readInputFile(inputFilePath);
    }
}

std::string TextParaphraser::readInputFile(const std::string& inputFilePath){
    std::ifstream inputFileReader;
    std::string inputFileText;

    inputFileReader.open(inputFilePath);
    
    if (!inputFileReader.is_open()){
        throw std::runtime_error("Can not open input file.");
    }

    for (int i = 0; !inputFileReader.eof(); i++){
        std::string line;
        getline(inputFileReader, line);

        inputFileText += (i == 0 ? line : "\n" + line);
    }

    inputFileReader.close();

    return inputFileText;
}

void TextParaphraser::paraphraseText(){
    for (std::string& word : splitInputTextIntoWords()){
        if (wordRequiresModification(word)){
            word = createWordReplacement(word);
        }
        
        outputText += word + " ";
    }

    outputText.pop_back(); // Remove trailing space
}

bool TextParaphraser::wordRequiresModification(const std::string& word){
    if (word.length() <= 3){
        return false;
    }

    return true;
}

std::vector<std::string> TextParaphraser::splitInputTextIntoWords(){
    std::vector<std::string> words;

    std::stringstream ss(inputText);
    std::string buffer;

    while(ss >> buffer){
        words.push_back(buffer);
    }

    return words;
}

std::string TextParaphraser::createWordReplacement(const std::string& word){
    SynonymFinder synonymFinder(word);
    std::vector<std::string> synonyms = synonymFinder.synonyms;
    
    bool provideMultipleSuggestions = JSONUtils::objectHasKey(
        argumentParser.parsedBoolArgs,
        "--multiple-suggestions"
    );

    if (provideMultipleSuggestions){
        return createMultipleSuggestionsList(synonyms, word);
    }
    else {
        return (synonyms.size() == 0 ? word : synonyms.at(0));
    }
}

std::string TextParaphraser::createMultipleSuggestionsList
    (const std::vector<std::string>& synonyms, const std::string& word){
    std::string suggestionsList = "(";

    for (const std::string& suggestion : synonyms){
        suggestionsList += suggestion + "/";
    }

    suggestionsList += word; // Include original word as a suggestion
    suggestionsList += ")";

    return suggestionsList;
}