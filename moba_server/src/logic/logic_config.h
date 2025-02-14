// src/logic/logic_config.h
#pragma once
#include <string>
#include <toml++/toml.hpp>

struct LogicConfig {
    struct RedisConfig {
        std::string host;
        int port;
        std::string password;
        int db_index;
        int pool_size;
    };

    RedisConfig redis;

    // 添加静态解析方法
    static LogicConfig parse(const toml::table& tbl);
};