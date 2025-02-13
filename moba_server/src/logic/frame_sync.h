#ifndef FRAME_SYNC_H
#define FRAME_SYNC_H

#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include "../common/redis_pool.h"

class FrameSync {
public:
    FrameSync():worker_thread_(&FrameSync::SyncThread, this) {};
    void Start();       // 启动同步线程
    void Stop();        // 停止同步线程
    void AddInput(const std::vector<char>& data);
    std::vector<char> GetNextFrame();

private:
    void SyncThread();  // 同步线程主循环

    std::vector<std::vector<char>> frames_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::atomic<bool> running_{false};
    std::thread worker_thread_;
};

#endif