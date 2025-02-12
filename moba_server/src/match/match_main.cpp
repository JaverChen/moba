#include <thread>
#include <chrono>
#include "../common/redis_pool.h"
#include "match_pool.h"

class MatchServer {
public:
    MatchServer() {
        redis_pool_.Init("127.0.0.1", 6379, 10);
        match_pool_.Start();
    }

    void Run() {
        while (true) {
            auto candidates = FetchCandidates();
            auto matches = match_algo_.FindMatches(candidates);
            PublishMatches(matches);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

private:
    std::vector<Player> FetchCandidates() {
        auto conn = redis_pool_.GetConnection();
        // 从Redis获取匹配队列
        return {};
    }

    RedisPool redis_pool_;
    MatchAlgorithm match_algo_;
    MatchPool match_pool_;
};

int main() {
    MatchServer server;
    server.Run();
    return 0;
}