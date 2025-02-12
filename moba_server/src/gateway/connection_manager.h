// src/gateway/connection_manager.h
#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include <unordered_set>
#include <memory>
#include <mutex>
#include "connection.h"  // 包含完整定义

class ConnectionManager {
public:
    void Start(Connection::pointer c);
    void Stop(Connection::pointer c);
    void StopAll();

    size_t Count() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return connections_.size();
    }

private:
    std::unordered_set<Connection::pointer> connections_;
    mutable std::mutex mutex_;
};

#endif // CONNECTION_MANAGER_H