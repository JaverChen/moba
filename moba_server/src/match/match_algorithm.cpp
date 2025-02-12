#include "match_algorithm.h"

std::vector<MatchResult> MatchAlgorithm::FindMatches(const std::vector<Player>& players) {
    std::vector<MatchResult> results;
    // 实现匹配算法
    return results;
}

bool MatchAlgorithm::IsMatchValid(const Player& p1, const Player& p2) const {
    return abs(p1.mmr - p2.mmr) < 100;
}