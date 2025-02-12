#include "frame_sync.h"

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