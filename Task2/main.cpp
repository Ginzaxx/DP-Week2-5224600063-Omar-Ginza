#include <iostream>
#include <vector>
#include <memory>
#include "GameSession.h"
#include "DeicideCard.h"
#include "DeicideBondRule.h"
#include "DeicideScoringRule.h"
#include "DeicideWinCondition.h"
#include "DeicideShopSystem.h"

// ============================================================
// main() — merakit semua komponen, inject ke GameSession.
//
// Phase 1 (GenerateHand) dan Phase 2 (SelectCards) sengaja
// dibiarkan placeholder di GameSession karena implementasi
// penuhnya memerlukan sistem Deck + input player yang
// di luar scope skeletal ini.
// ============================================================
int main() {
    DeicideBondRule     bond;
    DeicideScoringRule  scoring;
    DeicideWinCondition win;
    DeicideShopSystem   shop;

    GameSession session(&bond, &scoring, &win, &shop, 300);
    session.Start();

    return 0;
}
