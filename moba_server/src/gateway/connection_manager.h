// src/gateway/connection_manager.h
#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include <unordered_set>
#include <memory>
#include <mutex>
#include "connection.h"

class ConnectionManager {
public:
    static ConnectionManager& Instance(boost::asio::io_context& io);

    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;

    void Start(Connection::pointer c);
    void Stop(Connection::pointer c);
    void StopAll();
    void Broadcast(const std::vector<char>& data);
    void AddConnection(Connection::pointer conn);
    void RemoveConnection(Connection::pointer conn);
    void StartHealthCheck();
    void CheckConnections();

private:
    explicit ConnectionManager(boost::asio::io_context& io)
       : check_timer_(io) {}
    std::unordered_set<Connection::pointer> connections_;
    mutable std::mutex mutex_;
    boost::asio::steady_timer check_timer_;
};

#endif // CONNECTION_MANAGER_H