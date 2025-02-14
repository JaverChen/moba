#pragma once
#include <string>
#include <toml++/toml.hpp>
#include <filesystem>  // 添加文件系统库支持
#include <iostream>

class ConfigLoader {
public:
    template<typename T>
    static T Load(const std::string& path) {
        try {
            // 打印当前工作目录
            std::cout << "Current working directory: " 
                      << std::filesystem::current_path() << std::endl;
            
            // 打印尝试加载的配置文件路径
            std::cout << "Trying to load config file: " 
                      << std::filesystem::absolute(path) << std::endl;

            auto config = toml::parse_file(path);
            return T::parse(*config.as_table());
        } catch (const toml::parse_error& err) {
            // 捕获并输出详细错误信息
            std::string error_desc = "Config parse error: ";
            error_desc += err.description();
            error_desc += "\nFile path: ";
            error_desc += std::filesystem::absolute(path).string();
            throw std::runtime_error(error_desc);
        }
    }
};