#pragma once

class IWinCondition {
public:
    virtual bool IsWin(int score, int goal) = 0;
    virtual int  NextGoal(int currentGoal)  = 0;
    virtual ~IWinCondition() = default;
};
