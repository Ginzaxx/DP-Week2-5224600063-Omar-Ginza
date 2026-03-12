#pragma once
#include "ICardSelector.h"
#include <iostream>

// Implementasi Phase 2 -- otomatis mainkan semua kartu (scripted)
//
// Untuk ganti ke implementasi nyata:
//   buat PlayerInputSelector yang baca input keyboard
//   inject ke GameSession di main.cpp -- selesai
class AutoCardSelector : public ICardSelector {
public:
    std::vector<std::unique_ptr<ICard>> SelectCards(
        std::vector<std::unique_ptr<ICard>>& hand) override
    {
        std::cout << "  (scripted: play all " << hand.size() << " cards)\n";
        std::vector<std::unique_ptr<ICard>> selected;
        for (auto& c : hand)
            selected.push_back(std::move(c));
        hand.clear();
        return selected;
    }
};
