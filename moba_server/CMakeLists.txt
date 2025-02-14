cmake_minimum_required(VERSION 3.15)
project(MobaServer)

# 基础设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Protocol Buffer生成目录
set(PROTO_GEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/proto/generated)
file(MAKE_DIRECTORY ${PROTO_GEN_DIR})
find_package(Protobuf REQUIRED)
#set(Protobuf_IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/proto)
protobuf_generate_cpp(
    PROTO_SRCS 
    PROTO_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/proto/game.proto
    PROTOC_OUT_DIR ${PROTO_GEN_DIR}
)

# 依赖查找
find_package(Boost 1.71.0 REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

# MySQL/Hiredis手动配置
set(MYSQL_INCLUDE_DIR "/usr/include/mysql")
set(MYSQL_LIBRARY "/usr/lib/x86_64-linux-gnu/libmysqlclient.so")
set(HIREDIS_LIB "/usr/lib/x86_64-linux-gnu/libhiredis.so")


# 网关服务
add_executable(Gateway
    src/gateway/gateway_main.cpp
    src/gateway/connection_manager.cpp
    src/gateway/ssl_wrapper.cpp
    src/common/protocol.cpp
    ${PROTO_SRCS}
)
target_include_directories(Gateway PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${MYSQL_INCLUDE_DIR}
    ${PROTO_GEN_DIR}
    ${OpenSSL_INCLUDE_DIR}
)
target_link_libraries(Gateway
    protobuf::libprotobuf
    ${Boost_LIBRARIES}
    ${MYSQL_LIBRARY}
    ${HIREDIS_LIB}
    OpenSSL::SSL
    ${CMAKE_THREAD_LIBS_INIT}
)
# 逻辑服务
add_executable(Logic
    src/logic/logic_main.cpp
    src/logic/logic_config.cpp
    src/logic/frame_sync.cpp
    src/logic/battle_simulator.cpp
    src/common/protocol.cpp
    src/common/redis_pool.cpp
    ${PROTO_SRCS}
)
target_link_libraries(Logic
    protobuf::libprotobuf
    ${HIREDIS_LIB}
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENSSL_LIBRARIES}
)

# 安装规则
install(TARGETS Gateway Logic
    DESTINATION bin
    PERMISSIONS 
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE
)