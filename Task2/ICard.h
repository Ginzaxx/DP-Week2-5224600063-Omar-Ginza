#pragma once
#include <string>

class ICard {
public:
    virtual std::string GetName()    const = 0;
    virtual int         GetJourney() const = 0;
    virtual int         GetCycle()   const = 0;
    virtual void        SetJourney(int j)  = 0;
    virtual void        SetCycle(int c)    = 0;
    virtual ~ICard() = default;
};
