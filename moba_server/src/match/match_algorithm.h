#ifndef MATCH_ALGORITHM_H
#define MATCH_ALGORITHM_H

#include <vector>
#include "protocol.h"

class MatchAlgorithm {
public:
    std::vector<MatchResult> FindMatches(const std::vector<Player>& players);

private:
    bool IsMatchValid(const Player& p1, const Player& p2) const;
};

#endif