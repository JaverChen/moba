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

    void Start();
    void Stop();

private:
    explicit Connection(socket_type&& socket);
    void DoRead();
    void ProcessData(size_t length);

    socket_type socket_;
    std::array<char, 1024> buffer_;
};

#endif // CONNECTION_H