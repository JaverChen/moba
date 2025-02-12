#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <vector>
#include "../proto/generated/game.pb.h"

class Protocol {
public:
    static std::vector<char> Encode(const GameMessage& msg);
    static GameMessage Decode(const std::vector<char>& data);
};

#endif