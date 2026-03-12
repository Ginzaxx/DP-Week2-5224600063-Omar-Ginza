#pragma once
#include "IScoringRule.h"
#include <iostream>

// Placeholder: rumus nyata = totalJourney * totalCycle
class DeicideScoringRule : public IScoringRule {
public:
    int ComputeScore(const std::vector<std::unique_ptr<ICard>>& cards) override {
        int j = 0, c = 0;
        for (const auto& card : cards) {
            j += card->GetJourney();
            c += card->GetCycle();
        }
        int score = j * c;
        std::cout << "  [placeholder] Journey=" << j
                  << " Cycle=" << c
                  << " => Score=" << score << "\n";
        return score;
    }
};
