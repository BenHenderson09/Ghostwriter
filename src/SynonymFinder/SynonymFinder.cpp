#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include "SynonymFinder.hpp"
#include "../util/JSONUtils/ObjectHasKey.hpp"

std::vector<std::string> SynonymFinder::findSynonymsOfWord(const std::string& word){
    std::string responseString = queryApiForSynonyms(buildApiEndpoint(word));

    return extractSynonymsFromResponse(responseString);
}

namespace {
    std::string buildApiEndpoint(const std::string& word){
        return "https://wordsapiv1.p.rapidapi.com/words/" +  word + "/synonyms";
    }

    std::string queryApiForSynonyms(const std::string& apiEndpoint){
        std::string responseString;

        CURL* curl = createCurlSession(apiEndpoint);
        setHttpHeaders(curl);
        linkResponseString(curl, &responseString);
        executeRequest(curl);

        return responseString;
    }

    CURL* createCurlSession(const std::string& apiEndpoint){
        CURL* curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, apiEndpoint.c_str());
        
        return curl;
    }

    void setHttpHeaders(CURL* curl){
        struct curl_slist *headers = NULL;

        headers = curl_slist_append(headers, WordApiConfig::API_HOST_HEADER.c_str());
        headers = curl_slist_append(headers, WordApiConfig::API_KEY_HEADER.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }

    void linkResponseString(CURL* curl, std::string* responseString){
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, responseString);
    }

    size_t writeFunction(char* buffer,
            size_t sizeOfOneDataItem,
            size_t numberOfDataItems,
            std::string* data) {
        data->append(buffer, sizeOfOneDataItem * numberOfDataItems);

        return sizeOfOneDataItem * numberOfDataItems;
    }

    void executeRequest(CURL* curl){
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    std::vector<std::string> extractSynonymsFromResponse
            (const std::string& responseString){
        bool isResponseInJsonFormat = responseString[0] == '{';

        if (!isResponseInJsonFormat) return {};

        nlohmann::json jsonResponse = nlohmann::json::parse(responseString);

        bool doesResponseIncludeSynonyms = 
            JSONUtils::objectHasKey(jsonResponse, "synonyms");    

        if (doesResponseIncludeSynonyms){
            nlohmann::json synonyms = jsonResponse["synonyms"];

            return synonyms.get<std::vector<std::string>>();
        }

        return {};
    }
}