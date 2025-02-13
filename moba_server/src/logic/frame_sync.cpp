#include "frame_sync.h"
#include "../common/protocol.h"
#include <chrono>

void FrameSync::Start() {
    running_.store(true);
}

void FrameSync::Stop() {
    running_.store(false);
    cv_.notify_all();
    if (worker_thread_.joinable()) {
        worker_thread_.join();
    }
}

void FrameSync::SyncThread() {
    while (running_.load()) {
        auto conn = RedisPool::Instance().GetConnection();
        if (!conn) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        // 使用BRPOP保证线程安全
        redisReply* reply = (redisReply*)redisCommand(
            conn, "BRPOP frame_queue 1");
        
        if (reply && reply->type == REDIS_REPLY_ARRAY) {
            std::vector<char> data(
                reply->element[1]->str,
                reply->element[1]->str + reply->element[1]->len);
            
            {
                std::lock_guard<std::mutex> lock(mutex_);
                frames_.push_back(data);
                cv_.notify_one();
            }
        }
        
        freeReplyObject(reply);
        RedisPool::Instance().ReleaseConnection(conn);
    }
}

void FrameSync::AddInput(const std::vector<char>& data) {
    std::lock_guard<std::mutex> lock(mutex_);
    frames_.push_back(data);
    cv_.notify_one();
}

std::vector<char> FrameSync::GetNextFrame() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this]{ return !frames_.empty(); });
    auto frame = frames_.front();
    frames_.erase(frames_.begin());
    return frame;
}