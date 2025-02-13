struct GatewayConfig {
    struct Network {
        int listen_port = 8888; // 默认值
        std::string ssl_cert = "server.crt";
        std::string ssl_key = "server.key";
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
    // 其他配置段...
};

// TOML反序列化特化
template<>
struct toml::from<GatewayConfig> {
    static GatewayConfig from_toml(const toml::table& tbl) {
        return GatewayConfig{
            .network = {
                .listen_port = tbl["network"]["listen_port"].value_or(8888),
                .max_connections = tbl["network"]["max_connections"].value_or(1000),
                .ssl_enabled = tbl["network"]["ssl_enabled"].value_or(false),
                .ssl_cert = tbl["network"]["ssl_cert"].value_or(""),
                .ssl_key = tbl["network"]["ssl_key"].value_or("")
            },
            .database = {
                .host = tbl["database"]["mysql_host"].value_or("localhost"),
                .port = tbl["database"]["mysql_port"].value_or(3306),
                .user = tbl["database"]["mysql_user"].value_or("root"),
                .password = tbl["database"]["mysql_password"].value_or(""),
                .dbname = tbl["database"]["mysql_dbname"].value_or("moba")
            }
        };
    }
};