#ifndef TEXT_PARAPHRASER_HPP
#define TEXT_PARAPHRASER_HPP

#include <string>
#include <vector>
#include <thread>
#include "../CLIArgumentContainer/CLIArgumentContainer.hpp"

namespace TextParaphraser {
    std::string paraphraseText(CLIArgumentContainer argumentContainer);
};

#endif