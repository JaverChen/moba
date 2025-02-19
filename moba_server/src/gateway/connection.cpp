#include "connection.h" 

void Connection::Start() {
    DoRead();
}

void Connection::Stop() {
    boost::system::error_code ec;
    ssl_socket_->lowest_layer().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    ssl_socket_->lowest_layer().close();
}

void Connection::DoRead() {
    auto self(shared_from_this());
    ssl_socket_->async_read_some(
        boost::asio::buffer(buffer_),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                ProcessData(length);
                DoRead();
            }
        });
}

void Connection::ProcessData(size_t length) {
    try {
        // 协议解析
        std::vector<char> data(buffer_.begin(), buffer_.begin() + length);
        auto frame = Protocol::Decode(data);
        
        // 转发到逻辑服务器
        auto redis_conn = RedisPool::Instance().GetConnection();
        redisCommand(redis_conn, "RPUSH frame_queue %b", 
                    data.data(), data.size());
        RedisPool::Instance().ReleaseConnection(redis_conn);
        
    } catch (const std::exception& e) {
        LOG_INFO("Invalid data format: " + std::string(e.what()));
        Stop();
    }
}