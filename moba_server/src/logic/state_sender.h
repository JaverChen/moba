#pragma once
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp> 
#include "../proto/generated/game.pb.h"

class StateSender {
public:
    StateSender(const std::string& gateway_ip, int port) 
        : endpoint_(boost::asio::ip::make_address(gateway_ip), port),
            socket_(io_context_) 
    {
        Connect();
        // 启动IO上下文线程
        io_thread_ = std::thread([this](){ io_context_.run(); });
    }
    ~StateSender() {
        io_context_.stop();
        if(io_thread_.joinable()) io_thread_.join();
    }

    void SendWithRetry(const moba::GameState& state);

private:
    void Connect();
    void Reconnect();

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::endpoint endpoint_;
    boost::asio::ip::tcp::socket socket_;
    std::thread io_thread_;
};