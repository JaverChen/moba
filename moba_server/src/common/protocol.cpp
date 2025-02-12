#include "protocol.h"

std::vector<char> Protocol::Encode(const GameMessage& msg) {
    std::vector<char> buffer(msg.ByteSizeLong());
    msg.SerializeToArray(buffer.data(), buffer.size());
    return buffer;
}

GameMessage Protocol::Decode(const std::vector<char>& data) {
    GameMessage msg;
    msg.ParseFromArray(data.data(), data.size());
    return msg;
}