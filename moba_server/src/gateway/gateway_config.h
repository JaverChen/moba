#pragma once
#include <string>
#include <toml++/toml.hpp>

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

    Network network;
    Database database;

    // 添加静态解析方法
    static GatewayConfig parse(const toml::table& tbl);
};

// 实现解析方法
inline GatewayConfig GatewayConfig::parse(const toml::table& tbl) {
    GatewayConfig config;
    
    // 解析 Network 配置
    if (auto network_table = tbl["network"].as_table()) {
        config.network.listen_port      = network_table->get("listen_port")->value_or(8888);
        config.network.max_connections  = network_table->get("max_connections")->value_or(1000);
        config.network.ssl_enabled      = network_table->get("ssl_enabled")->value_or(false);
        config.network.ssl_cert         = network_table->get("ssl_cert")->value_or("");
        config.network.ssl_key          = network_table->get("ssl_key")->value_or("");
    }

    // 解析 Database 配置
    if (auto db_table = tbl["database"].as_table()) {
        config.database.host     = db_table->get("mysql_host")->value_or("localhost");
        config.database.port     = db_table->get("mysql_port")->value_or(3306);
        config.database.user     = db_table->get("mysql_user")->value_or("root");
        config.database.password = db_table->get("mysql_password")->value_or("");
        config.database.dbname   = db_table->get("mysql_dbname")->value_or("moba");
    }

    return config;
}