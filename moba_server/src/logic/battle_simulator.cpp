#include "battle_simulator.h"

void BattleSimulator::Simulate(const std::vector<moba::PlayerInput>& inputs) {
    // 实现战斗逻辑
    for (const auto& input : inputs) {
        // 更新游戏状态
    }
}

moba::GameState BattleSimulator::GetState() const {
    return state_;
}