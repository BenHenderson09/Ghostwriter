#ifndef JSON_OBJECT_HAS_KEY_HPP
#define JSON_OBJECT_HAS_KEY_HPP

#include <string>
#include <nlohmann/json.hpp>

bool JSONObjectHasKey(const nlohmann::json& object, const std::string& key);

#endif