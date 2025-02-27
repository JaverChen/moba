#include "frame_sync.h"
#include "battle_simulator.h"
#include "../common/redis_pool.h"
#include "logic_config.h"
#include "../common/config_loader.h"
#include "../common/logger.h"
#include <iostream>
#include <string>
#include "state_sender.h"

int main(int argc, char* argv[]) {
    try {
        auto config = ConfigLoader::Load<LogicConfig>("../conf/logic.toml");

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
        LOG_INFO("LogicServer starting...");

        // 初始化StateSender（新增）
        StateSender state_sender(config.gateway.gateway_ip, config.gateway.gateway_port); 
        
        // 启动帧同步系统
        FrameSync sync_system;
        BattleSimulator simulator;
        sync_system.Start();
        
        // 主循环
        while (true) {
            auto raw_data = sync_system.GetNextFrame();
            auto frame_data = Protocol::Decode<moba::FrameData>(raw_data);
            simulator.Simulate(frame_data.inputs());
            auto game_state = simulator.GetState();

            // 使用StateSender发送（替换原有Redis发布）
            state_sender.SendWithRetry(game_state); // 含压缩和重试逻辑

            LOG_DEBUG("Processed frame: {}", frame_data.frame_num());
        }
        
        sync_system.Stop();
    } catch (std::exception& e) {
        LOG_ERROR("Critical error: {}", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}