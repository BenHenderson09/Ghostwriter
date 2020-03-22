#ifndef SYNONYM_FINDER_HPP
#define SYNONYM_FINDER_HPP

#include <vector>
#include <string>
#include "../config/WordApiConfig.hpp"

class SynonymFinder {
    public:
        SynonymFinder(const std::string& word);

        std::vector<std::string> synonyms;

    private:
        const std::string& word;
        std::string apiEndpoint;

        void buildApiEndpoint();
        void findSynonymsOfWord();
        std::string queryApiForSynonyms();
        CURL* createCurlSession();
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
};

#endif