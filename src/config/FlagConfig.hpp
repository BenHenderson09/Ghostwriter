#ifndef FLAGCONFIG_HPP
#define FLAGCONFIG_HPP

#include <nlohmann/json.hpp>

namespace FlagConfig {
    const nlohmann::json FLAG_CONFIGURATIONS = {
        {
        "--input-text", {
                {"flagName", "inputText"},
                {"type", "string"}
            }
        },

        {
            "--input-file", {
                {"flagName", "inputFile"},
                {"type", "string"}
            },
        },

        {
            "--output-file", {
                {"flagName", "outputFile"},
                {"type", "string"}
            },
        },

        {
            "--multiple-suggestions", {
                {"flagName", "multipleSuggestions"},
                {"type", "bool"}
            } 
        }
    };
}

#endif