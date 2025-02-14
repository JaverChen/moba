#include "frame_sync.h"
#include "../common/redis_pool.h"
#include "logic_config.h"
#include "../common/config_loader.h"

int main() {
    // 加载配置
    auto config = ConfigLoader::Load<LogicConfig>("logic.toml");
    
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
    return 0;
}