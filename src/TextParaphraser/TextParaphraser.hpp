#ifndef TEXTPARAPHRASER_HPP
#define TEXTPARAPHRASER_HPP

#include <string>
#include <vector>
#include "../CLIArgumentParser/CLIArgumentParser.hpp"

class TextParaphraser {
    public:
        TextParaphraser(const CLIArgumentParser& argumentParser);
        TextParaphraser() = default;

        std::string outputText;

    private:
        const CLIArgumentParser& argumentParser;
        std::string inputText;
        bool isOutputLocationAFile;

        void organizeInputText();
        std::string readInputFile(const std::string& inputFilePath);
        void determineOutputLocation();
        void paraphraseText();
        std::vector<std::string> splitInputTextIntoWords();
        bool wordRequiresModification(const std::string& word);
        std::string createWordReplacement(const std::string& word);
        std::string createMultipleSuggestionsList
            (const std::vector<std::string>& synonyms, const std::string& word);
};

#endif