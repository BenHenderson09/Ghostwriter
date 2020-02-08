#include <iostream>
#include "CLIArgumentParser/CLIArgumentParser.hpp"

int main(int argc, char** argv){
    CLIArgumentParser argumentParser(argv);
    
    for (auto& item : argumentParser.parsedBoolArgs){
        std::cout << item.first << " | " << item.second << "\n";
    }

    for (auto& item : argumentParser.parsedStringArgs){
        std::cout << item.first << " | " << item.second << "\n";
    }

    return 0;
}