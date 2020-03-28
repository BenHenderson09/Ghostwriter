#ifndef TEXT_PARAPHRASER_HPP
#define TEXT_PARAPHRASER_HPP

#include <string>
#include <vector>
#include <thread>
#include "../CLIArgumentContainer/CLIArgumentContainer.hpp"

// "Public" items
namespace TextParaphraser {
    std::string paraphraseText(CLIArgumentContainer argumentContainer_);
};

// "Private" items
namespace {
    CLIArgumentContainer argumentContainer;
    std::string inputText;
    bool isOutputLocationAFile;

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
}

#endif