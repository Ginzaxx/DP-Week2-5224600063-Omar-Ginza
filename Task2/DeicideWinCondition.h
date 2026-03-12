#pragma once
#include "IWinCondition.h"
#include <iostream>

// Placeholder: menang jika score >= goal; goal naik x1.5 tiap round
class DeicideWinCondition : public IWinCondition {
public:
    bool IsWin(int score, int goal) override {
        bool win = score >= goal;
        std::cout << "  [placeholder] " << (win ? "WIN" : "LOSE") << "\n";
        return win;
    }
    int NextGoal(int currentGoal) override {
        return (int)(currentGoal * 1.5);
    }
};
