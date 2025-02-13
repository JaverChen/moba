#include <chrono>
#include "frame_sync.h"
#include "common/redis_pool.h"

void FrameSync::RunSyncLoop() {
    while (running_) {
        auto conn = RedisPool::Instance().GetConnection();
        auto reply = redisCommand(conn, "BLPOP frame_queue 1");
        
        if (reply && reply->elements > 0) {
            std::vector<char> data(
                reply->element[1]->str, 
                reply->element[1]->str + reply->element[1]->len
            );
            AddInput(data);
        }
        
        freeReplyObject(reply);
        RedisPool::Instance().ReleaseConnection(conn);
        
        // 固定频率广播（示例30Hz）
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
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