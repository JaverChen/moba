# moba
# 架构
moba_server/
├── src/
│   ├── common/
│   │   ├── config_loader.h
│   │   ├── protocol.cpp
│   │   ├── protocol.h
│   │   ├── logger.h
│   │   ├── mysql_pool.h
│   │   ├── mysql_pool.cpp
│   │   ├── redis_pool.h
│   │   └── redis_pool.cpp
│   ├── gateway/              #网关服务
│   │   ├── connection.h
│   │   ├── connection.cpp
│   │   ├── gateway_main.cpp
│   │   ├── gateway_config.h
│   │   ├── ssl_wrapper.h
│   │   ├── ssl_wrapper.cpp
│   │   ├── connection_manager.cpp
│   │   └── connection_manager.cpp
│   ├── logic/                # 逻辑服务
│   │   ├── frame_sync.h
│   │   ├── frame_sync.cpp
│   │   ├── battle_simulator.h
│   │   ├── battle_simulator.cpp
│   │   ├── logic_config.h
│   │   ├── logic_config.cpp
│   │   └── logic_main.cpp
│   └── proto/
│       ├── game.proto
│       └── generated/
│           ├── game.pb.cc
│           └── game.pb.h
└── conf
    ├── gateway.toml
    └── logic.toml