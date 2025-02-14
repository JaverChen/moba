#include "frame_sync.h"
#include "../common/redis_pool.h"
#include "logic_config.h"
#include "../common/config_loader.h"
#include <iostream>
#include <string>

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
        // 加载配置
        auto config = ConfigLoader::Load<LogicConfig>(config_path);
        
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