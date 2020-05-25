#include <sstream>
#include <vector>
#include <thread>
#include <curl/curl.h>
#include "paraphraseText.hpp"
#include "../CLIArgumentHolder/CLIArgumentHolder.hpp"
#include "../util/findSynonymsOfWord/findSynonymsOfWord.hpp"
#include "../util/readFile/readFile.hpp"

namespace {
    std::vector<std::string> splitInputTextIntoWords(const std::string& inputText);
    std::string findInputText(const CLIArgumentHolder& arguments);
    std::vector<std::thread> createWordModificationThreads
        (std::vector<std::string>& inputTextAsWords, const CLIArgumentHolder& arguments);
    bool wordRequiresModification(const std::string& word);    
    std::thread createWordModificationThread(std::string& word, const CLIArgumentHolder& arguments);
    void modifyWord(std::string& word, const CLIArgumentHolder& arguments);
    std::string createMultipleSuggestionsList
        (const std::vector<std::string>& synonyms, const std::string& word);
    std::string formatOutputText(const std::vector<std::string>& inputTextAsWords);

    std::vector<std::string> splitInputTextIntoWords(const std::string& inputText){
        std::vector<std::string> words;

        std::stringstream ss{inputText};
        std::string buffer;

        while(ss >> buffer){
            words.push_back(buffer);
        }

        return words;
    }

    std::string findInputText(const CLIArgumentHolder& arguments){
        bool isInputTextProvidedAsArgument{arguments.wasArgProvided("--input-text")};

        if (isInputTextProvidedAsArgument){
            return arguments.getParsedStringArg("--input-text");
        }
        else {
            std::string inputFilePath{arguments.getParsedStringArg("--input-file")};

            return readFile(inputFilePath);
        }
    }

    std::vector<std::thread> createWordModificationThreads
            (std::vector<std::string>& inputTextAsWords, const CLIArgumentHolder& arguments){
        std::vector<std::thread> wordModificationThreads;

        for (std::string& word : inputTextAsWords){
            if (wordRequiresModification(word)){
                wordModificationThreads.push_back(
                    createWordModificationThread(word, arguments)
                );
            }
        }

        return wordModificationThreads;
    }

    bool wordRequiresModification(const std::string& word){
        if (word.length() <= 3){
            return false;
        }

        return true;
    }

    std::thread createWordModificationThread(std::string& word, const CLIArgumentHolder& arguments){
        std::thread wordModificationThread(
            &modifyWord,
            std::ref(word),
            arguments
        );

        return wordModificationThread;
    }

    void modifyWord(std::string& word, const CLIArgumentHolder& arguments){
        std::vector<std::string> synonyms{findSynonymsOfWord(word)};
        
        bool areMultipleSuggestionsProvided{arguments.wasArgProvided("--multiple-suggestions")};

        if (areMultipleSuggestionsProvided){
            word = createMultipleSuggestionsList(synonyms, word);
        }
        else {
            word = (synonyms.size() == 0 ? word : synonyms.at(0));
        }
    }

    std::string createMultipleSuggestionsList
            (const std::vector<std::string>& synonyms, const std::string& word){
        std::string suggestionsList{"("};

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
    std::vector<std::string> inputTextAsWords = splitInputTextIntoWords(findInputText(arguments));
    std::vector<std::thread> wordModificationThreads{
        createWordModificationThreads(inputTextAsWords, arguments)
    };

    for (std::thread& thread : wordModificationThreads){
        thread.join();
    }

    return formatOutputText(inputTextAsWords);
}