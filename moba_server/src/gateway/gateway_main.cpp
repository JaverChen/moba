// src/gateway/gateway_main.cpp
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "connection_manager.h"
#include "gateway_config.h"
#include "ssl_wrapper.h"
#include "../common/config_loader.h"

using namespace boost::asio;
using namespace boost::asio::ip;

class Gateway {
public:
    void ReloadConfig(); 
    
    Gateway(io_context& io, const GatewayConfig& config)
        : acceptor_(io, tcp::endpoint(tcp::v4(), config.network.listen_port)),
            context_(ssl::context::tls_server),
            conn_mgr_() {
        // 从配置加载证书
        context_.use_certificate_file(config.network.ssl_cert, ssl::context::pem);
        context_.use_private_key_file(config.network.ssl_key, ssl::context::pem);
        StartAccept();
    }

private:
    void StartAccept() {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
                    auto ssl_socket = std::make_shared<ssl::stream<tcp::socket>>(
                        std::move(socket), context_);
                    // 使用weak_ptr避免循环引用
                    std::weak_ptr<ssl::stream<tcp::socket>> weak_ssl = ssl_socket;
                    ssl_socket->async_handshake(
                        ssl::stream_base::server,
                        [this, weak_ssl](const auto& ec) {
                            if (auto ssl_socket = weak_ssl.lock()) {
                                if (!ec) {
                                    auto conn = Connection::Create(std::move(*ssl_socket));
                                    conn_mgr_.Start(conn);
                                }
                            }
                        });
                }
                StartAccept();
            });
    }

    tcp::acceptor acceptor_;
    ssl::context context_;
    ConnectionManager conn_mgr_;
};

// void Gateway::ReloadConfig() {
//     auto new_config = ConfigLoader::Load<GatewayConfig>(config_path_);
//     ApplyNewConfig(new_config); // 实现配置生效逻辑
//     Logger::Info("Configuration reloaded successfully");
// }

int main() {
    try {
        auto config = ConfigLoader::Load<GatewayConfig>("gateway.toml");
        io_context io;
        Gateway server(io, config);
        io.run();
    } catch (std::exception& e) {
        std::cerr << "Gateway error: " << e.what() << std::endl;
    }
    return 0;
}