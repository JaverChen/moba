#pragma once
#include <string>
#include <toml++/toml.h>

class ConfigLoader {
public:
    template<typename T>
    static T Load(const std::string& path) {
        try {
            auto config = toml::parse_file(path);
            return toml::get<T>(config);
        } catch (const toml::parse_error& err) {
            throw std::runtime_error("Config parse error: " 
                + std::string(err.description()));
        }
    }
};