# 检查端口监听
netstat -tulnp | grep -E '888[8-9]|6379'

# 测试匹配系统
redis-cli LPUSH match_queue '{"player_id":1001,"mmr":1500}'