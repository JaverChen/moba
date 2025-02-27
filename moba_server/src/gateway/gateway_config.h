#pragma once
#include <string>
#include <toml++/toml.hpp>
#include <filesystem>

struct GatewayConfig {
    struct Network {
        int listen_port = 8888;
        std::string ssl_cert;
        std::string ssl_key;
        int max_connections;
        bool ssl_enabled;
    };

    struct Database {
        std::string host;
        int port;
        std::string user;
        std::string password;
        std::string dbname;
    };

    struct Log {
        std::string path = "gateway.log";
        std::string level = "info";
        std::string max_size = "100MB";
        int backup_count = 3;
        bool daemon_mode = false;
    };

    struct RedisConfig {
        std::string host = "127.0.0.1";
        int port = 6379;
        std::string password;
        int db_index = 1;
        int pool_size = 20;
    };

    Network network;
    Database database;
    Log log;
    RedisConfig redis;

    // 添加静态解析方法
    static GatewayConfig parse(const toml::table& tbl, const std::string& config_path);
};

// 实现解析方法
inline GatewayConfig GatewayConfig::parse(const toml::table& tbl, const std::string& config_path) {
    GatewayConfig config;
    
    // 解析 Network 配置
    if (auto network_table = tbl["network"].as_table()) {
        config.network.listen_port      = network_table->get("listen_port")->value_or(8888);
        config.network.max_connections  = network_table->get("max_connections")->value_or(1000);
        config.network.ssl_enabled      = network_table->get("ssl_enabled")->value_or(false);
        config.network.ssl_cert         = network_table->get("ssl_cert")->value_or("");
        config.network.ssl_key          = network_table->get("ssl_key")->value_or("");

        // 处理 SSL 证书路径（如果是相对路径，转为绝对路径）
        // 获取配置文件所在目录
        std::filesystem::path config_dir = std::filesystem::path(config_path).parent_path();

        // 处理 SSL 证书路径
        if (!config.network.ssl_cert.empty()) {
            std::filesystem::path cert_path(config.network.ssl_cert);
            if (cert_path.is_relative()) {
                cert_path = config_dir / cert_path;
            }
            config.network.ssl_cert = cert_path.string();
        }
        if (!config.network.ssl_key.empty()) {
            std::filesystem::path key_path(config.network.ssl_key);
            if (key_path.is_relative()) {
                key_path = config_dir / key_path;
            }
            config.network.ssl_key = key_path.string();
        }
    }

    // 解析 Database 配置
    if (auto db_table = tbl["database"].as_table()) {
        config.database.host     = db_table->get("mysql_host")->value_or("localhost");
        config.database.port     = db_table->get("mysql_port")->value_or(3306);
        config.database.user     = db_table->get("mysql_user")->value_or("root");
        config.database.password = db_table->get("mysql_password")->value_or("");
        config.database.dbname   = db_table->get("mysql_dbname")->value_or("moba");
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