#include "connection.h" 
#include "../common/logger.h"
#include "../common/protocol.h"
#include "../common/redis_pool.h"
#include "../common/crc32.h"
#include "exception_handler.h"
#include "../common/redis_pool.h"
#include "connection_manager.h"

std::atomic<uint32_t> Connection::global_id_{0};

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
            } else {
                ExceptionHandler::HandleConnectionError(shared_from_this(), ec);
            }
        });
}

void Connection::ProcessData(size_t length) {
    try {
        // 协议解析
        std::vector<char> data(buffer_.begin(), buffer_.begin() + length);
        // 校验数据完整性
        if (!DataValidator::Validate(data)) {
            LOG_ERROR("Invalid data checksum from {}", GetClientIP());
            return;
        }
        auto frame = Protocol::Decode<moba::FrameData>(data);
        
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

// 活性检测方法
bool Connection::CheckAlive() {
    // 发送PING帧
    const char ping_frame[] = {0x08}; // Protobuf field 1, varint 0
    boost::system::error_code ec;
    ssl_socket_->write_some(boost::asio::buffer(ping_frame), ec);
    
    // 检查响应（带超时）
    if (!ec) {
        std::array<char, 1> pong;
        ssl_socket_->async_read_some(
            boost::asio::buffer(pong),
            [](auto...){} // 忽略响应内容
        );
        return true;
    }
    return false;
}

void Connection::AsyncSend(const std::vector<char>& data) {
    // 将数据加入发送队列
    {
        std::lock_guard<std::mutex> lock(send_mutex_);
        send_queue_.push_back(data);
    }
    
    // 触发异步发送（若当前无发送操作）
    if (!is_sending_) {
        StartAsyncSend();
    }
}

void Connection::StartAsyncSend() {
    std::vector<boost::asio::const_buffer> buffers;
    {
        std::lock_guard<std::mutex> lock(send_mutex_);
        if (send_queue_.empty()) {
            is_sending_ = false;
            return;
        }
        
        // 合并所有待发送数据
        for (const auto& data : send_queue_) {
            buffers.push_back(boost::asio::buffer(data));
        }
        is_sending_ = true;
    }

    // 异步批量发送
    boost::asio::async_write(
        ssl_socket_->next_layer(), // 使用TCP层避免SSL分帧
        buffers,
        [this](boost::system::error_code ec, size_t bytes_sent) {
            std::lock_guard<std::mutex> lock(send_mutex_);
            send_queue_.clear(); // 清空已发送数据
            is_sending_ = false;
            
            if (ec) {
                LOG_WARN("Send failed: {}", ec.message());
                ConnectionManager::Instance(io_context_).RemoveConnection(shared_from_this());
            }
        }
    );
}

void Connection::CloseGracefully() { 
    Stop();
}