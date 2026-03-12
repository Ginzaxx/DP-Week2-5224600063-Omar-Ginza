#pragma once
#include "IWinCondition.h"
#include <iostream>

class DeicideWinCondition : public IWinCondition {
public:
    bool IsWin(int score, int goal) override {
        std::cout << "  score " << score << "  vs  goal " << goal << "\n";
        return score >= goal;
    }
    int NextGoal(int currentGoal) override {
        return (int)(currentGoal * 1.5);
    }
};
