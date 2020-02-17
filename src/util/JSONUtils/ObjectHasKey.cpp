#include "ObjectHasKey.hpp"

#include <string>
#include <nlohmann/json.hpp>

bool JSONUtils::objectHasKey
    (const nlohmann::json& object, const std::string& key){
    return object.find(key) != object.end();
}