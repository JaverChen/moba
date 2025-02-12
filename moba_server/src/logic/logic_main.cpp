#include <boost/asio.hpp>
#include "../common/redis_pool.h"
#include "frame_sync.h"
#include "battle_simulator.h"

class LogicServer {
public:
    LogicServer(unsigned short port) : udp_socket_(io_context_, udp::endpoint(udp::v4(), port)) {
        StartReceive();
        frame_thread_ = std::thread(&LogicServer::FrameLoop, this);
    }

    void Run() { io_context_.run(); }

private:
    void StartReceive() {
        udp_socket_.async_receive_from(
            boost::asio::buffer(recv_buffer_), remote_endpoint_,
            [this](boost::system::error_code ec, std::size_t bytes_recvd) {
                if (!ec) {
                    ProcessInput(bytes_recvd);
                    StartReceive();
                }
            });
    }

    void ProcessInput(size_t bytes) {
        auto input = Protocol::DecodeInput(recv_buffer_.data(), bytes);
        frame_sync_.AddInput(input);
    }

    void FrameLoop() {
        constexpr auto interval = std::chrono::milliseconds(33);
        while (running_) {
            auto frame_data = frame_sync_.CollectFrame();
            battle_sim_.Simulate(frame_data);
            BroadcastState();
            std::this_thread::sleep_for(interval);
        }
    }

    boost::asio::io_context io_context_;
    udp::socket udp_socket_;
    udp::endpoint remote_endpoint_;
    std::array<char, 1024> recv_buffer_;
    FrameSync frame_sync_;
    BattleSimulator battle_sim_;
    std::thread frame_thread_;
    std::atomic<bool> running_{true};
};

int main() {
    LogicServer server(8889);
    server.Run();
    return 0;
}