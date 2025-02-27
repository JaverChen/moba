#pragma once
#include "connection.h"
#include <map>

class ExceptionHandler {
public:
    static void HandleConnectionError(
        Connection::pointer conn, 
        const boost::system::error_code& ec
    ) {
        const static std::map<boost::system::error_code, std::string> error_map = {
            {boost::asio::error::eof, "客户端主动断开"},
            {boost::asio::error::connection_reset, "连接被重置"},
            {boost::asio::error::timed_out, "操作超时"}
        };
        
        auto it = error_map.find(ec);
        if (it != error_map.end()) {
            LOG_WARN("连接异常: {}", it->second);
        } else {
            LOG_ERROR("未知错误: {} ({})", ec.message(), ec.value());
        }
        
        conn->CloseGracefully();
    };
};