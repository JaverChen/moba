# 网关服务
/opt/moba/bin/Gateway --config /etc/moba/gateway.toml

# 逻辑服务（启动4个实例）
for i in {1..4}; do
    /opt/moba/bin/Logic --port $((8888+i)) --worker ${i} &
done

# 匹配服务
/opt/moba/bin/Match --redis 127.0.0.1:6379