#ifndef BATTLE_SIMULATOR_H
#define BATTLE_SIMULATOR_H

#include <vector>
#include "../common/protocol.h"

class BattleSimulator {
public:
    void Simulate(const std::vector<moba::PlayerInput>& inputs);
    moba::GameState GetState() const;

private:
    moba::GameState state_;
};

#endif