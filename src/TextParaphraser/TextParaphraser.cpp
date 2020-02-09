#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <curl/curl.h>
#include "TextParaphraser.hpp"
#include "../CLIArgumentParser/CLIArgumentParser.hpp"
#include "../SynonymFinder/SynonymFinder.hpp"
#include "../util/JSONUtils/ObjectHasKey.hpp"

TextParaphraser::TextParaphraser(CLIArgumentParser argumentParser){
    this->argumentParser = argumentParser;
    organizeInputText();
    paraphraseText();
}

void TextParaphraser::organizeInputText(){
    bool isInputTextProvidedAsArgument = JSONUtils::objectHasKey(
        argumentParser.parsedStringArgs,
        "--input-text"
    );

    if (isInputTextProvidedAsArgument){
        inputText = argumentParser.parsedStringArgs["--input-text"];
    }
    else {
        std::string inputFilePath =
            argumentParser.parsedStringArgs["--input-file"];

        inputText = readInputFile(inputFilePath);
    }
}

std::string TextParaphraser::readInputFile(std::string inputFilePath){
    std::ifstream inputFileReader;
    std::string inputFileText;

    inputFileReader.open(inputFilePath);
    
    for(int i = 0; !inputFileReader.eof(); i++){
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

bool TextParaphraser::wordRequiresModification(std::string word){
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

std::string TextParaphraser::createWordReplacement(std::string word){
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
    (std::vector<std::string> synonyms, std::string word){
    synonyms.push_back(word); // Include word as a suggestion
    std::string suggestionsList = "(";

    for (std::string suggestion : synonyms){
        suggestionsList += suggestion + "/";
    }

    suggestionsList.pop_back(); // Remove trailing slash
    suggestionsList += ")";

    return suggestionsList;
}