// src/gateway/connection.h
#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>

class Connection : public std::enable_shared_from_this<Connection> {
public:
    using pointer = std::shared_ptr<Connection>;
    using socket_type = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;

    static pointer Create(std::shared_ptr<socket_type> ssl_socket, boost::asio::io_context& io) {
        return pointer(new Connection(ssl_socket, io));
    }

    void Start();
    void Stop();
    bool CheckAlive();
    void AsyncSend(const std::vector<char>& data);
    void CloseGracefully();

    uint32_t GetID() const { return id_; }
    
    std::string GetClientIP() const {
        boost::system::error_code ec;
        auto endpoint = ssl_socket_->lowest_layer().remote_endpoint(ec);
        return ec ? "unknown" : endpoint.address().to_string();
    }

private:
    explicit Connection(std::shared_ptr<socket_type> ssl_socket, boost::asio::io_context& io)
        : ssl_socket_(ssl_socket), io_context_(io) {}

    void DoRead();
    void ProcessData(size_t length);
    void StartAsyncSend();

    std::shared_ptr<socket_type> ssl_socket_; // 使用 shared_ptr 管理
    std::array<char, 1024> buffer_;
    std::vector<std::vector<char>> send_queue_;
    std::mutex send_mutex_;
    bool is_sending_ = false;
    static std::atomic<uint32_t> global_id_;
    uint32_t id_ = ++global_id_;
    boost::asio::io_context& io_context_;
};