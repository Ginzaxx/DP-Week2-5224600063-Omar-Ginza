#pragma once
#include <vector>
#include <memory>
#include "ICard.h"

// Interface Phase 1 -- generate hand kartu untuk player
// Implementasi bisa: scripted, random dari Deck, draft, dll
class IHandGenerator {
public:
    virtual std::vector<std::unique_ptr<ICard>> GenerateHand() = 0;
    virtual ~IHandGenerator() = default;
};
