#pragma once
#include <vector>
#include "../common/protocol.h"

class BattleSimulator {
public:
    void Simulate(const google::protobuf::RepeatedPtrField<moba::PlayerInput>& inputs);
    moba::Player* GetOrCreatePlayer(uint32_t id);
    moba::GameState GetState() const;

private:
    moba::GameState state_;
};