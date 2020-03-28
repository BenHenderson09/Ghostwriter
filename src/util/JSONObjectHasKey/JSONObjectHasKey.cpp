#include <string>
#include <nlohmann/json.hpp>
#include "JSONObjectHasKey.hpp"

bool JSONObjectHasKey(const nlohmann::json& object, const std::string& key){
    return object.find(key) != object.end();
}