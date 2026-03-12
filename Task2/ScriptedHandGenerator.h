#pragma once
#include "IHandGenerator.h"
#include "DeicideCard.h"
#include <iostream>

// Implementasi Phase 1 -- kartu scripted per round
// Menunjukkan skenario bond berbeda tiap round:
//   Round 1: Kephale + Nikador  -> HEATED RIVALRY
//   Round 2: Janus + Talanton + Oronyx -> TITAN FATE
//   Round 3: Demiurge + Kephale -> CYCLE BEGINNING
//   Round 4+: hand lemah, tidak ada bond -> GAME OVER
//
// Untuk ganti ke implementasi nyata:
//   buat RandomHandGenerator yang ambil dari Deck
//   inject ke GameSession di main.cpp -- selesai
class ScriptedHandGenerator : public IHandGenerator {
private:
    int round = 0;

public:
    std::vector<std::unique_ptr<ICard>> GenerateHand() override {
        round++;
        std::vector<std::unique_ptr<ICard>> hand;

        if (round == 1) {
            hand.push_back(std::make_unique<DeicideCard>("Kephale",  100, 1));
            hand.push_back(std::make_unique<DeicideCard>("Nikador",   80, 1));
            hand.push_back(std::make_unique<DeicideCard>("Thanatos",  40, 2));
        } else if (round == 2) {
            hand.push_back(std::make_unique<DeicideCard>("Janus",      1, 6));
            hand.push_back(std::make_unique<DeicideCard>("Talanton",   5, 4));
            hand.push_back(std::make_unique<DeicideCard>("Oronyx",    15, 3));
        } else if (round == 3) {
            hand.push_back(std::make_unique<DeicideCard>("Demiurge", 100, 6));
            hand.push_back(std::make_unique<DeicideCard>("Kephale",  100, 1));
            hand.push_back(std::make_unique<DeicideCard>("Georios",   75, 1));
        } else {
            hand.push_back(std::make_unique<DeicideCard>("Zegreus",   10, 4));
            hand.push_back(std::make_unique<DeicideCard>("Cerces",     5, 6));
        }

        std::cout << "  Hand dealt:\n";
        for (const auto& c : hand)
            std::cout << "    + " << c->GetName()
                      << "  J:" << c->GetJourney()
                      << "  C:" << c->GetCycle() << "\n";
        return hand;
    }
};
