#include "frame_sync.h"
#include "../common/redis_pool.h"
#include "logic_config.h"
#include "../common/config_loader.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    try {
        auto config = ConfigLoader::Load<GatewayConfig>("../conf/logic.toml");

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
        
        // 启动帧同步系统
        FrameSync sync_system;
        sync_system.Start();
        
        // 主循环
        while (true) {
            auto frame = sync_system.GetNextFrame();
            // 处理帧逻辑...
        }
        
        sync_system.Stop();
    } catch (std::exception& e) {
        std::cerr << "LogicServer error: " << e.what() << std::endl;
    }
    return 0;
}