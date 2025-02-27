#include "protocol.h"

std::vector<char> Protocol::Encode(const moba::FrameData& msg) {
    std::vector<char> buffer(msg.ByteSizeLong());
    msg.SerializeToArray(buffer.data(), buffer.size());
    return buffer;
}