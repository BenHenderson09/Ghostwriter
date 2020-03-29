#ifndef CREATE_DUMMY_CLI_ARG_CONTAINER_HPP
#define CREATE_DUMMY_CLI_ARG_CONTAINER_HPP

#include <string>
#include <initializer_list>
#include "../../../src/CLIArgumentContainer/CLIArgumentContainer.hpp"

CLIArgumentContainer createDummyCLIArgContainer
        (const std::initializer_list<std::string>& args = {});

#endif