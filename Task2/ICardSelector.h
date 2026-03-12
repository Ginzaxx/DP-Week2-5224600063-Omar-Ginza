#pragma once
#include <vector>
#include <memory>
#include "ICard.h"

// Interface Phase 2 -- player memilih kartu dari hand
// Implementasi bisa: scripted, input keyboard, AI, dll
class ICardSelector {
public:
    virtual std::vector<std::unique_ptr<ICard>> SelectCards(
        std::vector<std::unique_ptr<ICard>>& hand) = 0;
    virtual ~ICardSelector() = default;
};
