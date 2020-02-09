#ifndef TEXTPARAPHRASER_HPP
#define TEXTPARAPHRASER_HPP

#include <string>
#include <vector>
#include "../CLIArgumentParser/CLIArgumentParser.hpp"

class TextParaphraser {
    public:
        TextParaphraser(CLIArgumentParser argumentParser);
        TextParaphraser() = default;

        std::string outputText;

    private:
        CLIArgumentParser argumentParser;
        std::string inputText;
        bool isOutputLocationAFile;

        void organizeInputText();
        std::string readInputFile(std::string inputFilePath);
        void determineOutputLocation();
        void paraphraseText();
        std::vector<std::string> splitInputTextIntoWords();
        bool wordRequiresModification(std::string word);
        std::string createWordReplacement(std::string word);
        std::string createMultipleSuggestionsList
            (std::vector<std::string> synonyms, std::string word);
};

#endif