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

using namespace boost::asio;
using namespace boost::asio::ip;

class Gateway {
public:
    Gateway(io_context& io, const GatewayConfig& config)
        : acceptor_(io, tcp::endpoint(tcp::v4(), config.network.listen_port)),
          context_(ssl::context::tls_server),
          conn_mgr_() {
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
                                auto conn = Connection::Create(ssl_socket);
                                conn_mgr_.Start(conn);
                            }
                        }
                    );
                }
                StartAccept();
            });
    }

    tcp::acceptor acceptor_;
    ssl::context context_;
    ConnectionManager conn_mgr_;
};

int main(int argc, char* argv[]) {
    try {
        // 检查命令行参数
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <config_file_path>" << std::endl;
            return 1;
        }
        // 获取配置文件路径
        std::string config_path = argv[1];
        std::cout << "Loading config from: " << config_path << std::endl;

        auto config = ConfigLoader::Load<GatewayConfig>(config_path);
        io_context io;
        Gateway server(io, config);
        io.run();
    } catch (std::exception& e) {
        std::cerr << "Gateway error: " << e.what() << std::endl;
    }
    return 0;
}