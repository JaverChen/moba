#ifndef BATTLE_SIMULATOR_H
#define BATTLE_SIMULATOR_H

#include <vector>
#include "protocol.h"

class BattleSimulator {
public:
    void Simulate(const std::vector<PlayerInput>& inputs);
    GameState GetState() const;

private:
    GameState state_;
};

#endif