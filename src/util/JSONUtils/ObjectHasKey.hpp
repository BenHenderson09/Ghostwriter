#ifndef OBJECT_HAS_KEY_HPP
#define OBJECT_HAS_KEY_HPP

#include <string>
#include <nlohmann/json.hpp>

namespace JSONUtils {
    bool objectHasKey(const nlohmann::json& object, const std::string& key);
}

#endif