#include <fstream>
#include "readFile.hpp"

namespace {
    void checkForFileReadingErrors(const std::ifstream& inputFileReader){
    if (!inputFileReader.is_open()){
        throw std::runtime_error("Can not open input file.");
    }
}

    std::string extractInputFileContents(std::ifstream& inputFileReader){
        std::string contents;

        for (int i = 0; !inputFileReader.eof(); i++){
            std::string line;
            getline(inputFileReader, line);

            contents += (i == 0 ? line : "\n" + line);
        }

        return contents;
    }
}

std::string readFile(const std::string& inputFilePath){
    std::ifstream inputFileReader;
    std::string inputFileContents;

    inputFileReader.open(inputFilePath);
    checkForFileReadingErrors(inputFileReader);
    inputFileContents = extractInputFileContents(inputFileReader);
    inputFileReader.close();

    return inputFileContents;
}