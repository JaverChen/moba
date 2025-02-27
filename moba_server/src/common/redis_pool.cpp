#include "redis_pool.h"

RedisPool& RedisPool::Instance() {
    static RedisPool instance;  // 确保静态实例存在
    return instance;
}

void RedisPool::Init(const char* host, int port, int max_conn) {
    max_connections_ = max_conn;
    host_ = host;
    port_ = port;
    for (int i = 0; i < max_conn; ++i) {
        auto conn = redisConnect(host, port);
        if (conn && !conn->err) {
            pool_.push(conn);
        }
    }
}

redisContext* RedisPool::GetConnection() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (pool_.empty()) {
        // 动态扩展连接池（新增逻辑）
        for (int i = 0; i < 2; ++i) { // 每次扩展2个连接
            auto conn = redisConnect(host_.c_str(), port_);
            if (conn && !conn->err) {
                pool_.push(conn);
            }
        }
        if (pool_.empty()) return nullptr;
    }
    auto conn = pool_.front();
    pool_.pop();
    return conn;
}

void RedisPool::ReleaseConnection(redisContext* conn) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (pool_.size() < max_connections_) {
        pool_.push(conn);
    } else {
        redisFree(conn);
    }
}

RedisPool::~RedisPool() {
    while (!pool_.empty()) {
        redisFree(pool_.front());
        pool_.pop();
    }
}

bool RedisPool::ExecuteCommand(const std::string& command, const std::vector<char>& data) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (pool_.empty()) return false;
    
    redisContext* conn = pool_.front();
    redisReply* reply = (redisReply*)redisCommand(conn, command.c_str(), data.data(), data.size());
    if (!reply || reply->type == REDIS_REPLY_ERROR) {
        freeReplyObject(reply);
        return false;
    }
    freeReplyObject(reply);
    return true;
}