#include <sstream>
#include <vector>
#include <thread>
#include <curl/curl.h>
#include "paraphraseText.hpp"
#include "../CLIArgumentHolder/CLIArgumentHolder.hpp"
#include "../util/findSynonymsOfWord/findSynonymsOfWord.hpp"
#include "../util/readFile/readFile.hpp"

namespace {
    // Variables
    CLIArgumentHolder arguments_;
    std::string inputText_;
    bool isOutputLocationAFile_;

    // Prototypes
    void organizeInputText();
    void determineOutputLocation();
    std::string applySynonymsToInputText();
    std::vector<std::string> splitInputTextIntoWords();
    bool wordRequiresModification(const std::string& word);
    std::thread createWordModificationThread(std::string& word);
    void modifyWord(std::string& word);
    
    std::string createMultipleSuggestionsList(
        const std::vector<std::string>& synonyms,
        const std::string& word
    );

    std::string formatOutputText(const std::vector<std::string>& inputTextAsWords);

    // Implementation
    void organizeInputText(){
        bool isInputTextProvidedAsArgument = arguments_.wasArgProvided("--input-text");

        if (isInputTextProvidedAsArgument){
            inputText_ = arguments_.getParsedStringArg("--input-text");
        }
        else {
            std::string inputFilePath = arguments_.getParsedStringArg("--input-file");

            inputText_ = readFile(inputFilePath);
        }
    }

    std::string applySynonymsToInputText(){
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

        return formatOutputText(inputTextAsWords);
    }

    std::thread createWordModificationThread(std::string& word){
        std::thread wordModificationThread(
            &modifyWord,
            std::ref(word)
        );

        return wordModificationThread;
    }

    bool wordRequiresModification(const std::string& word){
        if (word.length() <= 3){
            return false;
        }

        return true;
    }

    std::vector<std::string> splitInputTextIntoWords(){
        std::vector<std::string> words;

        std::stringstream ss(inputText_);
        std::string buffer;

        while(ss >> buffer){
            words.push_back(buffer);
        }

        return words;
    }

    void modifyWord(std::string& word){
        std::vector<std::string> synonyms = findSynonymsOfWord(word);
        
        bool areMultipleSuggestionsProvided =
            arguments_.wasArgProvided("--multiple-suggestions");

        if (areMultipleSuggestionsProvided){
            word = createMultipleSuggestionsList(synonyms, word);
        }
        else {
            word = (synonyms.size() == 0 ? word : synonyms.at(0));
        }
    }

    std::string createMultipleSuggestionsList
            (const std::vector<std::string>& synonyms, const std::string& word){
        std::string suggestionsList = "(";

        for (const std::string& suggestion : synonyms){
            suggestionsList += suggestion + "/";
        }

        suggestionsList += word; // Include original word as a suggestion
        suggestionsList += ")";

        return suggestionsList;
    }

    std::string formatOutputText(const std::vector<std::string>& inputTextAsWords){
        std::string outputText;
        
        for (std::string word : inputTextAsWords){
            outputText += word + " ";
        }

        outputText.pop_back(); // Remove trailing backslash
        return outputText;
    }
}

std::string paraphraseText(CLIArgumentHolder arguments){
    arguments_ = arguments;
    organizeInputText();
    
    return applySynonymsToInputText();
}