#include "state_sender.h"
#include "../common/logger.h"
#include "../common/compression.h"
#include "../common/crc32.h"

void StateSender::SendWithRetry(const moba::GameState& state) {
    try {
        // 压缩数据
        std::vector<char> raw(state.ByteSizeLong());
        state.SerializeToArray(raw.data(), raw.size());
        auto compressed = ZlibCompressor::Compress(raw);
        
        // 添加校验头
        auto final_data = DataValidator::AddChecksum(compressed);
        
        // 发送
        socket_.send(boost::asio::buffer(final_data));
    } catch (const boost::system::system_error& e) {
        LOG_ERROR("Send to gateway failed: {}", e.what());
        Reconnect();
    }
}

void StateSender::Connect() {
    socket_.connect(endpoint_);
    LOG_INFO("Connected to gateway at {}:{}", 
            endpoint_.address().to_string(), 
            endpoint_.port());
}

void StateSender::Reconnect() {
    using boost::asio::ip::tcp;
    if (socket_.is_open()) {
        boost::system::error_code ec;
        socket_.shutdown(tcp::socket::shutdown_both, ec);
        socket_.close(ec);
    }
    Connect();
}