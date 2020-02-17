#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "SynonymFinder.hpp"
#include "../util/JSONUtils/ObjectHasKey.hpp"

SynonymFinder::SynonymFinder(const std::string& word) : word(word) {
    buildApiEndpoint();
    findSynonymsOfWord();
}

void SynonymFinder::buildApiEndpoint(){
    apiEndpoint =
        "https://wordsapiv1.p.rapidapi.com/words/" +  word + "/synonyms";
}

void SynonymFinder::findSynonymsOfWord(){
    std::string responseString = queryApiForSynonyms();
    
    synonyms = extractSynonymsFromResponse(responseString);
}

std::string SynonymFinder::queryApiForSynonyms(){
    std::string responseString;

    CURL* curl = createCurlSession();
    setHttpHeaders(curl);
    linkResponseString(curl, &responseString);
    executeRequest(curl);

    return responseString;
}

CURL* SynonymFinder::createCurlSession(){
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, apiEndpoint.c_str());
    
    return curl;
}

void SynonymFinder::setHttpHeaders(CURL* curl){
    struct curl_slist *headers = NULL;

    headers =
        curl_slist_append(headers, WordApiConfig::API_HOST_HEADER.c_str());

    headers =
        curl_slist_append(headers, WordApiConfig::API_KEY_HEADER.c_str());

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
}

void SynonymFinder::linkResponseString(CURL* curl, std::string* responseString){
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, responseString);
}

size_t SynonymFinder::writeFunction(char* buffer,
        size_t sizeOfOneDataItem,
        size_t numberOfDataItems,
        std::string* data) {
    data->append(buffer, sizeOfOneDataItem * numberOfDataItems);

    return sizeOfOneDataItem * numberOfDataItems;
}

void SynonymFinder::executeRequest(CURL* curl){
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}

std::vector<std::string> SynonymFinder
    ::extractSynonymsFromResponse(const std::string& responseString){
    nlohmann::json response = nlohmann::json::parse(responseString);

    // If api recognizes word
    if (JSONUtils::objectHasKey(response, "synonyms")){
        nlohmann::json synonyms = response["synonyms"];

        return synonyms.get<std::vector<std::string>>();
    }

    return std::vector<std::string>();
}
