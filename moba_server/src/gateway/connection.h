// src/gateway/connection.h
#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>
#include "../common/protocol.h"
#include "../common/redis_pool.h"
#include "../common/logger.h"

class Connection : public std::enable_shared_from_this<Connection> {
public:
    using pointer = std::shared_ptr<Connection>;
    using socket_type = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;

    static pointer Create(std::shared_ptr<socket_type> ssl_socket) {
        return pointer(new Connection(ssl_socket));
    }

    void Start();
    void Stop();

private:
    explicit Connection(std::shared_ptr<socket_type> ssl_socket)
        : ssl_socket_(ssl_socket) {}

    void DoRead();
    void ProcessData(size_t length);

    std::shared_ptr<socket_type> ssl_socket_; // 使用 shared_ptr 管理
    std::array<char, 1024> buffer_;
};