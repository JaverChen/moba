#include "battle_simulator.h"
#include "../common/logger.h"
#include <cmath>
#include <fmt/format.h>

void BattleSimulator::Simulate(const google::protobuf::RepeatedPtrField<moba::PlayerInput>& inputs) {
    for (const auto& input : inputs) {
        // 基础移动计算（忽略碰撞）
        auto* player = GetOrCreatePlayer(input.player_id());
        const float speed = 5.0f; // 单位：米/秒
        const float delta_time = 1.0f / 30.0f; // 30Hz帧率
        
        // 更新位置
        player->mutable_position()->set_x(
            player->position().x() + input.move_dir().x() * speed * delta_time
        );
        player->mutable_position()->set_y(
            player->position().y() + input.move_dir().y() * speed * delta_time
        );
        player->mutable_position()->set_z(
            player->position().z() + input.move_dir().z() * speed * delta_time
        );

        LOG_TRACE(fmt::format("Player {} moved to ({},{},{})", 
                 input.player_id(),
                 player->position().x(),
                 player->position().y(),
                 player->position().z()));
    }
}

moba::GameState BattleSimulator::GetState() const {
    return state_;
}

moba::Player* BattleSimulator::GetOrCreatePlayer(uint32_t id) {
    auto it = std::find_if(state_.mutable_players()->begin(),
                          state_.mutable_players()->end(),
                          [id](const moba::Player& p) { 
                              return p.id() == id; 
                          });
    if (it == state_.mutable_players()->end()) {
        auto* new_player = state_.add_players();
        new_player->set_id(id);
        new_player->mutable_position()->set_x(0);
        new_player->mutable_position()->set_y(0);
        new_player->mutable_position()->set_z(0);
        return new_player;
    }
    return &(*it);
}