// src/gateway/connection.h
#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>

class Connection : public std::enable_shared_from_this<Connection> {
public:
    using pointer = std::shared_ptr<Connection>;
    using socket_type = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;

    static pointer Create(socket_type&& socket) {
        return pointer(new Connection(std::move(socket)));
    }

    void Start() {
        // 启动异步读写
        DoRead();
    }

    void Stop() {
        boost::system::error_code ec;
        socket_.lowest_layer().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        socket_.lowest_layer().close();
    }

private:
    explicit Connection(socket_type&& socket)
        : socket_(std::move(socket)) {}

    void DoRead() {
        auto self(shared_from_this());
        socket_.async_read_some(
            boost::asio::buffer(buffer_),
            [this, self](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    // 处理接收数据
                    ProcessData(length);
                    DoRead();
                }
            });
    }

    void ProcessData(size_t length) {
        // 实现协议解析逻辑
    }

    socket_type socket_;
    std::array<char, 1024> buffer_;
};

#endif // CONNECTION_H