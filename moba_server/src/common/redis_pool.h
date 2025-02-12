#ifndef REDIS_POOL_H
#define REDIS_POOL_H

#include <mutex>
#include <queue>
#include <hiredis/hiredis.h>

class RedisPool {
public:
    static RedisPool& Instance() {
        static RedisPool instance;
        return instance;
    }

    void Init(const char* host, int port, int max_conn);
    redisContext* GetConnection();
    void ReleaseConnection(redisContext* conn);

private:
    RedisPool() = default;
    ~RedisPool();

    std::queue<redisContext*> pool_;
    std::mutex mutex_;
    int max_connections_;
};

#endif