# moba
# 架构
moba_server/
├── src/
│   ├── common/
│   │   ├── config_loader.h
│   │   ├── compression.h
│   │   ├── crc32.h
│   │   ├── protocol.cpp
│   │   ├── protocol.h
│   │   ├── logger.h
│   │   ├── logger.cpp
│   │   ├── mysql_pool.h
│   │   ├── mysql_pool.cpp
│   │   ├── redis_pool.h
│   │   └── redis_pool.cpp
│   ├── gateway/              #网关服务
│   │   ├── exception_handler.h
│   │   ├── exception_handler.cpp
│   │   ├── connection.h
│   │   ├── connection.cpp
│   │   ├── gateway_main.cpp
│   │   ├── gateway_config.h
│   │   ├── ssl_wrapper.h
│   │   ├── ssl_wrapper.cpp
│   │   ├── connection_manager.cpp
│   │   └── connection_manager.cpp
│   ├── logic/                # 逻辑服务
│   │   ├── state_sender.h
│   │   ├── state_sender.cpp
│   │   ├── frame_sync.h
│   │   ├── frame_sync.cpp
│   │   ├── battle_simulator.h
│   │   ├── battle_simulator.cpp
│   │   ├── logic_config.h
│   │   └── logic_main.cpp
│   └── proto/
│       ├── game.proto
│       └── generated/
│           ├── game.pb.cc
│           └── game.pb.h
└── conf
    ├── gateway.toml
    └── logic.toml