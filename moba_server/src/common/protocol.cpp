#include "protocol.h"
#include <stdexcept>

std::vector<char> Protocol::Encode(const moba::FrameData& msg) {
    std::vector<char> buffer(msg.ByteSizeLong());
    msg.SerializeToArray(buffer.data(), buffer.size());
    return buffer;
}

moba::FrameData Protocol::Decode(const std::vector<char>& data) {
    moba::FrameData msg;
    if (!msg.ParseFromArray(data.data(), data.size())) {
        throw std::runtime_error("Protocol parse error");
    }
    return msg;
}