// src/gateway/connection_manager.cpp
#include "connection_manager.h"
#include "../common/logger.h"

ConnectionManager& ConnectionManager::Instance(boost::asio::io_context& io) {
    static ConnectionManager instance(io);
    return instance;
}

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

// 广播接口
void ConnectionManager::Broadcast(const std::vector<char>& data) {
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto& conn : connections_) {
        conn->AsyncSend(data); // 异步发送接口
    }
}

// 连接管理
void ConnectionManager::AddConnection(Connection::pointer conn) {
    std::lock_guard<std::mutex> lock(mutex_);
    connections_.insert(conn);
}

void ConnectionManager::RemoveConnection(Connection::pointer conn) {
    std::lock_guard<std::mutex> lock(mutex_);
    connections_.erase(conn);
}

// 定时检查线程
void ConnectionManager::StartHealthCheck() {
    check_timer_.expires_after(std::chrono::seconds(30));
    check_timer_.async_wait([this](auto ec) {
        if (!ec) CheckConnections();
        StartHealthCheck(); // 递归调用保持持续检查
    });
}

void ConnectionManager::CheckConnections() {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = connections_.begin();
    while (it != connections_.end()) {
        // 发送PING包检测连接活性
        if (!(*it)->CheckAlive()) {
            LOG_INFO("Removing inactive connection: {}", (*it)->GetID());
            it = connections_.erase(it);
        } else {
            ++it;
        }
    }
}