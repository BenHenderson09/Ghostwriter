#ifndef CREATE_DUMMY_CLI_ARG_HOLDER_HPP
#define CREATE_DUMMY_CLI_ARG_HOLDER_HPP

#include <string>
#include <initializer_list>
#include "../../../src/CLIArgumentHolder/CLIArgumentHolder.hpp"

CLIArgumentHolder createDummyCLIArgHolder
        (const std::initializer_list<std::string>& args = {});

#endif