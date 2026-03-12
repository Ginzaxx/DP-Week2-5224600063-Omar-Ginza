#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "ICard.h"
#include "IBondRule.h"
#include "IScoringRule.h"
#include "IWinCondition.h"
#include "IShopSystem.h"

// =============================================================
// GameSession — INVARIANT
//
// Tidak tahu: kartu apa, bond apa, cara hitung score,
//             kondisi menang, atau mekanik shop.
//
// Hanya tahu: urutan 6 fase yang harus dipanggil setiap round.
// Urutan ini TIDAK BOLEH berubah.
// =============================================================
class GameSession {
private:
    IBondRule*     bondRule;
    IScoringRule*  scoringRule;
    IWinCondition* winCondition;
    IShopSystem*   shopSystem;

    int  scoreGoal;
    int  currentRound;
    bool isRunning;

    // ── Fase-fase dipecah jadi private method yang terpisah ──

    // Phase 1 — Buat hand kartu untuk round ini
    std::vector<std::unique_ptr<ICard>> Phase_GenerateHand() {
        std::cout << "\n[Phase 1] Generate hand\n";
        // Placeholder — implementasi nyata ada di luar GameSession
        return {};
    }

    // Phase 2 — Player memilih kartu yang akan dimainkan
    std::vector<std::unique_ptr<ICard>> Phase_SelectCards(
        std::vector<std::unique_ptr<ICard>>& hand)
    {
        std::cout << "[Phase 2] Player selects cards\n";
        // Placeholder — implementasi nyata ada di luar GameSession
        return {};
    }

    // Phase 3 — Terapkan semua bond pada kartu yang dipilih
    void Phase_ApplyBonds(std::vector<std::unique_ptr<ICard>>& selected) {
        std::cout << "[Phase 3] Apply bonds\n";
        bondRule->Apply(selected);
    }

    // Phase 4 — Hitung score dari kartu yang sudah di-buff
    int Phase_ComputeScore(const std::vector<std::unique_ptr<ICard>>& selected) {
        std::cout << "[Phase 4] Compute score\n";
        return scoringRule->ComputeScore(selected);
    }

    // Phase 5 — Evaluasi hasil: menang atau kalah
    bool Phase_EvaluateResult(int score) {
        std::cout << "[Phase 5] Evaluate result"
                  << " | Score: " << score
                  << " / Goal: " << scoreGoal << "\n";
        return winCondition->IsWin(score, scoreGoal);
    }

    // Phase 6 — Buka shop (hanya jika menang)
    void Phase_OpenShop() {
        std::cout << "[Phase 6] Open shop\n";
        shopSystem->OpenShop();
    }

    // Advance — Naikkan goal dan round setelah shop selesai
    void Phase_AdvanceRound() {
        scoreGoal = winCondition->NextGoal(scoreGoal);
        currentRound++;
        std::cout << "\n>>> Round " << currentRound
                  << " starts | New goal: " << scoreGoal << "\n";
    }

public:
    GameSession(IBondRule*     bond,
                IScoringRule*  scoring,
                IWinCondition* win,
                IShopSystem*   shop,
                int            startGoal = 300)
        : bondRule(bond), scoringRule(scoring),
          winCondition(win), shopSystem(shop),
          scoreGoal(startGoal), currentRound(1), isRunning(true) {}

    // ==========================================================
    // Start() — INVARIANT LOOP
    // Urutan fase TIDAK BOLEH berubah.
    // ==========================================================
    void Start() {
        std::cout << "==============================\n";
        std::cout << "        DEICIDE — RUN\n";
        std::cout << "==============================\n";

        while (isRunning) {
            std::cout << "\n--- Round " << currentRound
                      << " | Goal: " << scoreGoal << " ---\n";

            auto hand     = Phase_GenerateHand();           // Phase 1
            auto selected = Phase_SelectCards(hand);        // Phase 2
            Phase_ApplyBonds(selected);                     // Phase 3
            int  score    = Phase_ComputeScore(selected);   // Phase 4
            bool won      = Phase_EvaluateResult(score);    // Phase 5

            if (won) {
                Phase_OpenShop();                           // Phase 6
                Phase_AdvanceRound();
            } else {
                isRunning = false;
            }
        }

        std::cout << "\n==============================\n";
        std::cout << "         GAME OVER\n";
        std::cout << " Reached Round: " << currentRound << "\n";
        std::cout << "==============================\n";
    }
};
