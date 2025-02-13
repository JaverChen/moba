#ifndef REDIS_POOL_H
#define REDIS_POOL_H

#include <hiredis/hiredis.h>
#include <queue>
#include <mutex>
#include <atomic>

class RedisPool {
public:
    static RedisPool& Instance() {
        static RedisPool instance;
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    RedisPool(const RedisPool&) = delete;
    RedisPool& operator=(const RedisPool&) = delete;

    void Init(const char* host, int port, int max_conn);
    redisContext* GetConnection();
    void ReleaseConnection(redisContext* conn);
    ~RedisPool();

private:
    RedisPool() = default; // 私有构造函数
    std::queue<redisContext*> pool_;
    std::mutex mutex_;
    int max_connections_ = 0;
};

#endif