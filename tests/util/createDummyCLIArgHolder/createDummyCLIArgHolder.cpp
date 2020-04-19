#include "../../../src/CLIArgumentHolder/CLIArgumentHolder.hpp"
#include "createDummyCLIArgHolder.hpp"

CLIArgumentHolder createDummyCLIArgHolder
        (const std::initializer_list<std::string>& args){
    std::string dummyArgs;
    dummyArgs += "--input-text placeholder text";

    for (const std::string& arg : args){
        dummyArgs += " " + arg;
    }

    return CLIArgumentHolder(dummyArgs);
}