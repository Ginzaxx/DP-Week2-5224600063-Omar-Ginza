#pragma once
#include <vector>
#include <memory>
#include "ICard.h"

class IBondRule {
public:
    virtual void Apply(std::vector<std::unique_ptr<ICard>>& cards) = 0;
    virtual ~IBondRule() = default;
};
