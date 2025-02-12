#ifndef FRAME_SYNC_H
#define FRAME_SYNC_H

#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>

class FrameSync {
public:
    void AddInput(const std::vector<char>& data);
    std::vector<char> GetNextFrame();

private:
    std::vector<std::vector<char>> frames_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::atomic<uint32_t> frame_counter_{0};
};

#endif