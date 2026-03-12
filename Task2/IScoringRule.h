#pragma once
#include <vector>
#include <memory>
#include "ICard.h"

class IScoringRule {
public:
    virtual int ComputeScore(const std::vector<std::unique_ptr<ICard>>& cards) = 0;
    virtual ~IScoringRule() = default;
};
