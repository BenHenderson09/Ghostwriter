#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <curl/curl.h>
#include "TextParaphraser.hpp"
#include "../CLIArgumentContainer/CLIArgumentContainer.hpp"
#include "../SynonymFinder/SynonymFinder.hpp"

TextParaphraser::TextParaphraser(CLIArgumentContainer& argumentContainer)
    : argumentContainer(argumentContainer){
    organizeInputText();
    paraphraseText();
}

void TextParaphraser::organizeInputText(){
    bool isInputTextProvidedAsArgument =
        argumentContainer.wasArgProvided("--input-text");

    if (isInputTextProvidedAsArgument){
        inputText =
            argumentContainer.getParsedStringArg("--input-text");
    }
    else {
        std::string inputFilePath =
            argumentContainer.getParsedStringArg("--input-file");

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
    std::vector<std::string> inputTextAsWords = splitInputTextIntoWords();
    std::vector<std::thread> wordModificationThreads;

    for (std::string& word : inputTextAsWords){
        if (wordRequiresModification(word)){
            wordModificationThreads.push_back(
                createWordModificationThread(word)
            );
        }
    }

    for (std::thread& thread : wordModificationThreads){
        thread.join();
    }

    formatOutputText(inputTextAsWords);
}

std::thread TextParaphraser::createWordModificationThread(std::string& word){
    std::thread wordModificationThread(
        &TextParaphraser::modifyWord,
        this,
        std::ref(word)
    );

    return wordModificationThread;
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

void TextParaphraser::modifyWord(std::string& word){
    SynonymFinder synonymFinder(word);
    
    std::vector<std::string> synonyms = synonymFinder.synonyms;
    
    bool areMultipleSuggestionsProvided =
        argumentContainer.getParsedBoolArg("--multiple-suggestions");

    if (areMultipleSuggestionsProvided){
        word = createMultipleSuggestionsList(synonyms, word);
    }
    else {
        word = (synonyms.size() == 0 ? word : synonyms.at(0));
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

void TextParaphraser::formatOutputText(std::vector<std::string> inputTextAsWords){
    for (std::string word : inputTextAsWords){
        outputText += word + " ";
    }

    outputText.pop_back(); // Remove trailing backslash
}