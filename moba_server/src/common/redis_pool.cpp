#include "redis_pool.h"

void RedisPool::Init(const char* host, int port, int max_conn) {
    max_connections_ = max_conn;
    for (int i = 0; i < max_conn; ++i) {
        auto conn = redisConnect(host, port);
        if (conn && !conn->err) {
            pool_.push(conn);
        }
    }
}

redisContext* RedisPool::GetConnection() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (pool_.empty()) return nullptr;
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