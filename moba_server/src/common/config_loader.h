#pragma once
#include <string>
#include <toml++/toml.hpp>

class ConfigLoader {
public:
    template<typename T>
    static T Load(const std::string& path) {
        try {
            // 解析配置文件
            auto config = toml::parse_file(path);
            return T::parse(*config.as_table(), path);
        } catch (const toml::parse_error& err) {
            throw std::runtime_error("Config parse error: " + std::string(err.description()));
        }
    }
};