#ifndef SYNONYM_FINDER_HPP
#define SYNONYM_FINDER_HPP

#include <vector>
#include <string>
#include "../config/WordApiConfig.hpp"

namespace SynonymFinder {
    std::vector<std::string> findSynonymsOfWord(const std::string& word);
}

#endif