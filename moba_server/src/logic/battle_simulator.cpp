#include "battle_simulator.h"

void BattleSimulator::Simulate(const std::vector<PlayerInput>& inputs) {
    // 实现战斗逻辑
    for (const auto& input : inputs) {
        // 更新游戏状态
    }
}

GameState BattleSimulator::GetState() const {
    return state_;
}