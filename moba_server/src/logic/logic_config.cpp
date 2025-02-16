#include "logic_config.h"

LogicConfig LogicConfig::parse(const toml::table& tbl, const std::string& config_path) {
    LogicConfig config;
    
    // 解析 Redis 配置
    if (auto redis_table = tbl["redis"].as_table()) {
        config.redis.host       = redis_table->get("host")->value_or("localhost");
        config.redis.port       = redis_table->get("port")->value_or(6379);
        config.redis.password   = redis_table->get("password")->value_or("");
        config.redis.db_index   = redis_table->get("db_index")->value_or(0);
        config.redis.pool_size  = redis_table->get("pool_size")->value_or(20);
    }

    return config;
}