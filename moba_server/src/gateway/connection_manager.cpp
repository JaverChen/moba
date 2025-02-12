// src/gateway/connection_manager.cpp
#include "connection_manager.h"
#include "connection.h"  // 明确包含头文件

void ConnectionManager::Start(Connection::pointer c) {
    std::lock_guard<std::mutex> lock(mutex_);
    connections_.insert(c);
    c->Start();
}

void ConnectionManager::Stop(Connection::pointer c) {
    std::lock_guard<std::mutex> lock(mutex_);
    connections_.erase(c);
    c->Stop();
}

void ConnectionManager::StopAll() {
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto& conn : connections_) {
        conn->Stop();
    }
    connections_.clear();
}