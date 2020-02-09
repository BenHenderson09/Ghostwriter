#include "ObjectHasKey.hpp"

#include <string>
#include <nlohmann/json.hpp>

bool JSONUtils::objectHasKey(nlohmann::json object, std::string key){
    return object.find(key) != object.end();
}