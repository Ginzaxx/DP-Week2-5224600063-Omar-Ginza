#include "GameSession.h"
#include "ScriptedHandGenerator.h"
#include "AutoCardSelector.h"
#include "DeicideBondRule.h"
#include "DeicideScoringRule.h"
#include "DeicideWinCondition.h"
#include "DeicideShopSystem.h"

// ============================================================
// main() -- merakit semua komponen, inject ke GameSession.
//
// Untuk ekspansi ke implementasi penuh, HANYA ganti ini:
//   ScriptedHandGenerator -> RandomHandGenerator (pakai Deck)
//   AutoCardSelector      -> PlayerInputSelector (input keyboard)
// GameSession tidak perlu disentuh sama sekali.
// ============================================================
int main() {
    ScriptedHandGenerator generator;  // Phase 1
    AutoCardSelector      selector;   // Phase 2
    DeicideBondRule       bond;       // Phase 3
    DeicideScoringRule    scoring;    // Phase 4
    DeicideWinCondition   win;        // Phase 5 & advance
    DeicideShopSystem     shop;       // Phase 6

    GameSession session(&generator, &selector,
                        &bond, &scoring, &win, &shop,
                        300);
    session.Start();
    return 0;
}
