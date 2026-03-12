#pragma once
#include "IScoringRule.h"
#include <iostream>

// Rumus: totalJourney * totalCycle
class DeicideScoringRule : public IScoringRule {
public:
    int ComputeScore(const std::vector<std::unique_ptr<ICard>>& cards) override {
        int j = 0, c = 0;
        for (const auto& card : cards) {
            j += card->GetJourney();
            c += card->GetCycle();
        }
        int score = j * c;
        std::cout << "  totalJourney=" << j
                  << "  totalCycle=" << c
                  << "  =>  Score = " << j << " x " << c << " = " << score << "\n";
        return score;
    }
};
