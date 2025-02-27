#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <vector>
#include "../proto/generated/game.pb.h"
#include <stdexcept>

class Protocol {
public:
    static std::vector<char> Encode(const moba::FrameData& msg);
    template<typename T>
    static T Decode(const std::vector<char>& data) {
        T msg;
        if (!msg.ParseFromArray(data.data(), data.size())) {
            throw std::runtime_error("Protocol parse error");
        }
        return msg;
    }
};

#endif