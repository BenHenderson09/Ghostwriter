#include "../../../src/CLIArgumentContainer/CLIArgumentContainer.hpp"
#include "createDummyCLIArgContainer.hpp"

CLIArgumentContainer createDummyCLIArgContainer
        (const std::initializer_list<std::string>& args){
    std::string dummyArgs;
    dummyArgs += "--input-text placeholder text";

    for (const std::string& arg : args){
        dummyArgs += " " + arg;
    }

    return CLIArgumentContainer(dummyArgs);
}