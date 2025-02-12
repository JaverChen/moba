cmake_minimum_required(VERSION 3.15)
project(MobaServer)

# 基础设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Protocol Buffer生成目录
set(PROTO_GEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/proto/generated)
file(MAKE_DIRECTORY ${PROTO_GEN_DIR})  # 确保目录存在
find_package(Protobuf REQUIRED)
set(Protobuf_IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/proto)

# 依赖查找
find_package(Boost 1.71.0 REQUIRED COMPONENTS system)
find_package(Protobuf REQUIRED)
find_package(OpenSSL REQUIRED)

# MySQL配置
find_path(MYSQL_INCLUDE_DIR mysql.h
    PATHS /usr/include/mysql
    REQUIRED
)
find_library(MYSQL_LIBRARY
    NAMES mysqlclient
    PATHS /usr/lib/x86_64-linux-gnu
    REQUIRED
)

# Hiredis配置
set(HIREDIS_INCLUDE_DIR "/usr/include/hiredis")
set(HIREDIS_LIBRARY "/usr/lib/x86_64-linux-gnu/libhiredis.so")

# 协议生成
protobuf_generate_cpp(
    PROTO_SRCS 
    PROTO_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/proto/game.proto
    PROTOC_OUT_DIR ${PROTO_GEN_DIR}
)

# 包含目录
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${MYSQL_INCLUDE_DIR}
    ${HIREDIS_INCLUDE_DIR}
    ${PROTO_GEN_DIR}
    ${Protobuf_INCLUDE_DIRS}
)

# 网关服务
add_executable(Gateway
    src/gateway/gateway_main.cpp
    src/gateway/connection_manager.cpp
    src/gateway/ssl_wrapper.cpp
    src/common/protocol.cpp
    ${PROTO_SRCS}
)

target_link_libraries(Gateway
    protobuf::libprotobuf
    ${Boost_LIBRARIES}
    ${MYSQL_LIBRARY}
    ${HIREDIS_LIBRARY}
    OpenSSL::SSL
    pthread
)
#[[
# 逻辑服务
add_executable(Logic
    src/logic/logic_main.cpp
    src/logic/frame_sync.cpp
    src/logic/battle_simulator.cpp
    src/common/protocol.cpp
    src/common/redis_pool.cpp
    ${PROTO_SRCS}
)
target_link_libraries(Logic
    protobuf::libprotobuf
    pthread
    ${HIREDIS_LIBRARIES}
)

# 匹配服务
add_executable(Match
    src/match/match_main.cpp
    src/match/match_algorithm.cpp
    src/match/match_pool.cpp
    src/common/protocol.cpp
    src/common/redis_pool.cpp
    ${PROTO_SRCS}
)
target_link_libraries(Match
    protobuf::libprotobuf
    ${HIREDIS_LIBRARIES}
)

# 安装规则
install(TARGETS Gateway Logic Match
    DESTINATION bin
    PERMISSIONS 
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE
)
]]
install(TARGETS Gateway
    DESTINATION bin
    PERMISSIONS 
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE
)