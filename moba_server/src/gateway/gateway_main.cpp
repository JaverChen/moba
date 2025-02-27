// src/gateway/gateway_main.cpp
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "connection_manager.h"
#include "gateway_config.h"
#include "ssl_wrapper.h"
#include "../common/config_loader.h"
#include <iostream>
#include <string>
#include <filesystem>
#include "../common/logger.h"
#include "../proto/generated/game.pb.h"
#include "../common/redis_pool.h"

using namespace boost::asio;
using namespace boost::asio::ip;

class Gateway {
public:
    Gateway(boost::asio::io_context& io, const GatewayConfig& config)
      : io_(io), 
        acceptor_(io, tcp::endpoint(tcp::v4(), config.network.listen_port)),
        context_(ssl::context::tls_server),
        conn_mgr_(ConnectionManager::Instance(io))
    {
        // 检查证书文件是否存在
        if (!std::filesystem::exists(config.network.ssl_cert)) {
            throw std::runtime_error("SSL certificate file not found: " + config.network.ssl_cert);
        }
        if (!std::filesystem::exists(config.network.ssl_key)) {
            throw std::runtime_error("SSL private key file not found: " + config.network.ssl_key);
        }
        // 加载证书
        context_.use_certificate_file(config.network.ssl_cert, ssl::context::pem);
        context_.use_private_key_file(config.network.ssl_key, ssl::context::pem);

        // 添加启动日志
        LOG_INFO("Gateway starting on port " + std::to_string(config.network.listen_port));
        LOG_INFO("SSL enabled: " + std::to_string(config.network.ssl_enabled));

        StartAccept();
    }

private:
    void StartAccept() {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
                    // 使用 shared_ptr 管理 ssl_socket
                    auto ssl_socket = std::make_shared<ssl::stream<tcp::socket>>(
                        std::move(socket), context_
                    );
                    // 异步握手
                    ssl_socket->async_handshake(
                        ssl::stream_base::server,
                        [this, ssl_socket](const boost::system::error_code& ec) {
                            if (!ec) {
                                // 将 ssl_socket 所有权传递给 Connection
                                auto conn = Connection::Create(ssl_socket, this->io_);
                                conn_mgr_.Start(conn);
                            }
                        }
                    );
                }else{
                    // 添加错误日志
                    LOG_INFO("Accept error: " + ec.message());
                }
                StartAccept();
            });
    }

    tcp::acceptor acceptor_;
    ssl::context context_;
    ConnectionManager& conn_mgr_;
    boost::asio::io_context& io_;
};

void StartStateReceiver(boost::asio::io_context& io, unsigned short port) {
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), port));

    std::function<void()> accept_handler;
    accept_handler = [&] {
        acceptor.async_accept(
            [&](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::array<char, 1024> buffer;
                    socket.read_some(boost::asio::buffer(buffer));
                    
                    // 解析为GameState并广播
                    moba::GameState state;
                    if (state.ParseFromArray(buffer.data(), buffer.size())) {
                        std::vector<char> data(buffer.begin(), buffer.end());
                        ConnectionManager::Instance(io).Broadcast(data);
                    }
                }
                accept_handler();  // 递归调用
            });
    };
}

int main(int argc, char* argv[]) {
    try {
        auto config = ConfigLoader::Load<GatewayConfig>("../conf/gateway.toml");

        // 初始化日志
        Logger::Config log_config{
            .path = config.log.path,
            .level = config.log.level,
            .max_size = config.log.max_size,
            .backup_count = config.log.backup_count,
            .daemon_mode = config.log.daemon_mode
        };
        Logger::Init(log_config);

        // 初始化Redis连接池
        RedisPool::Instance().Init(
            config.redis.host.c_str(),
            config.redis.port,
            config.redis.pool_size
        );

        // 服务器初始化
        LOG_INFO("Starting gateway server...");
        LOG_DEBUG("Network config: port={}, ssl={}", 
                config.network.listen_port, 
                config.network.ssl_enabled);
                
        // 启动服务器
        io_context io;
        Gateway server(io, config);

        LOG_INFO("Server started on port {}", config.network.listen_port); 
        //启动接收
        StartStateReceiver(io, 8887);
         // 启动健康检查
        ConnectionManager::Instance(io).StartHealthCheck();
        io.run();

    } catch (std::exception& e) {
        LOG_ERROR("Fatal error: " + std::string(e.what()));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}