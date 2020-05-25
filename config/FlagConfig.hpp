#ifndef FLAG_CONFIG_HPP
#define FLAG_CONFIG_HPP

#include <nlohmann/json.hpp>

namespace FlagConfig {
    const nlohmann::json FLAG_CONFIGURATIONS =
        {
            {
                "--input-text", {
                    {"type", "string"}
                }
            },

            {
                "--input-file", {
                    {"type", "string"}
                },
            },

            {
                "--output-file", {
                    {"type", "string"}
                },
            },

            {
                "--multiple-suggestions", {
                    {"type", "bool"}
                } 
            }
        };
}

#endif