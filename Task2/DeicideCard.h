#pragma once
#include "ICard.h"

// Kartu Deicide sederhana — Journey x Cycle = kontribusi score
class DeicideCard : public ICard {
    std::string name;
    int journey, cycle;
public:
    DeicideCard(std::string n, int j, int c)
        : name(n), journey(j), cycle(c) {}

    std::string GetName()    const override { return name; }
    int         GetJourney() const override { return journey; }
    int         GetCycle()   const override { return cycle; }
    void        SetJourney(int j)  override { journey = j; }
    void        SetCycle(int c)    override { cycle = c; }
};
