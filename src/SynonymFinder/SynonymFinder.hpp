#ifndef SYNONYM_FINDER_HPP
#define SYNONYM_FINDER_HPP

#include <vector>
#include <string>
#include "../config/WordApiConfig.hpp"

// "Public" items
namespace SynonymFinder {
    std::vector<std::string> findSynonymsOfWord(const std::string& word);
}

// "Private" items
namespace {
    std::string buildApiEndpoint(const std::string& word);
    std::string queryApiForSynonyms(const std::string& apiEndpoint);
    CURL* createCurlSession(const std::string& apiEndpoint);
    void setHttpHeaders(CURL* curl);
    void linkResponseString(CURL* curl, std::string* responseString);
    
    static size_t writeFunction(
        char* buffer,
        size_t sizeOfOneDataItem,
        size_t numberOfDataItems,
        std::string* data
    );
    
    void executeRequest(CURL* curl);
    std::vector<std::string>
        extractSynonymsFromResponse(const std::string& responseString);
}

#endif