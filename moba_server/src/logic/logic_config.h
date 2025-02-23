// src/logic/logic_config.h
#pragma once
#include <string>
#include <toml++/toml.hpp>
#include <filesystem>

struct LogicConfig {
    struct RedisConfig {
        std::string host;
        int port;
        std::string password;
        int db_index;
        int pool_size;
    };

    struct Log {
        std::string path = "gateway.log";
        std::string level = "info";
        std::string max_size = "100MB";
        int backup_count = 3;
        bool daemon_mode = false;
    };

    RedisConfig redis;
    Log log;

    // 添加静态解析方法
    static LogicConfig parse(const toml::table& tbl, const std::string& config_path);
};

inline LogicConfig LogicConfig::parse(const toml::table& tbl, const std::string& config_path) {
    LogicConfig config;
    
    // 解析 Redis 配置
    if (auto redis_table = tbl["redis"].as_table()) {
        config.redis.host       = redis_table->get("host")->value_or("localhost");
        config.redis.port       = redis_table->get("port")->value_or(6379);
        config.redis.password   = redis_table->get("password")->value_or("");
        config.redis.db_index   = redis_table->get("db_index")->value_or(0);
        config.redis.pool_size  = redis_table->get("pool_size")->value_or(20);
    }

     // 日志配置解析
     if (auto log_table = tbl["log"].as_table()) {
        config.log.level = log_table->get("level")->value_or("info");
        config.log.path = log_table->get("path")->value_or("");
        config.log.max_size = log_table->get("max_size")->value_or("100MB");
        config.log.backup_count = log_table->get("backup_count")->value_or(3);
        config.log.daemon_mode = log_table->get("daemon_mode")->value_or(false);

       // 处理相对路径
       std::filesystem::path config_dir = std::filesystem::path(config_path).parent_path();
       std::filesystem::path log_path(config.log.path);
       if (log_path.is_relative()) {
           log_path = config_dir / log_path;
           config.log.path = log_path.lexically_normal().string();
       }
    }

    return config;
}