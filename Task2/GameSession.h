#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "IHandGenerator.h"
#include "ICardSelector.h"
#include "IBondRule.h"
#include "IScoringRule.h"
#include "IWinCondition.h"
#include "IShopSystem.h"

// =============================================================
// GameSession -- INVARIANT
//
// Hanya tahu 6 interface.
//
// Untuk ganti apapun (scripted -> random -> input player):
// cukup inject implementasi berbeda di main.cpp.
// GameSession tidak perlu disentuh.
// =============================================================
class GameSession {
private:
    IHandGenerator* handGenerator;
    ICardSelector*  cardSelector;
    IBondRule*      bondRule;
    IScoringRule*   scoringRule;
    IWinCondition*  winCondition;
    IShopSystem*    shopSystem;

    int  scoreGoal;
    int  currentRound;
    bool isRunning;

    void printDivider(char c = '-', int width = 44) {
        for (int i = 0; i < width; i++) std::cout << c;
        std::cout << "\n";
    }

    void Phase_GenerateHand(std::vector<std::unique_ptr<ICard>>& out) {
        std::cout << "[Phase 1] Generate Hand\n";
        out = handGenerator->GenerateHand();
    }

    void Phase_SelectCards(std::vector<std::unique_ptr<ICard>>& hand,
                           std::vector<std::unique_ptr<ICard>>& out) {
        std::cout << "[Phase 2] Player Selects Cards\n";
        out = cardSelector->SelectCards(hand);
    }

    void Phase_ApplyBonds(std::vector<std::unique_ptr<ICard>>& selected) {
        std::cout << "[Phase 3] Apply Bonds\n";
        bondRule->Apply(selected);
    }

    int Phase_ComputeScore(const std::vector<std::unique_ptr<ICard>>& selected) {
        std::cout << "[Phase 4] Compute Score\n";
        return scoringRule->ComputeScore(selected);
    }

    bool Phase_EvaluateResult(int score) {
        std::cout << "[Phase 5] Evaluate Result\n";
        return winCondition->IsWin(score, scoreGoal);
    }

    void Phase_OpenShop() {
        std::cout << "[Phase 6] Open Shop\n";
        shopSystem->OpenShop();
    }

    void Phase_AdvanceRound() {
        scoreGoal = winCondition->NextGoal(scoreGoal);
        currentRound++;
    }

public:
    GameSession(IHandGenerator* generator,
                ICardSelector*  selector,
                IBondRule*      bond,
                IScoringRule*   scoring,
                IWinCondition*  win,
                IShopSystem*    shop,
                int             startGoal = 300)
        : handGenerator(generator), cardSelector(selector),
          bondRule(bond), scoringRule(scoring),
          winCondition(win), shopSystem(shop),
          scoreGoal(startGoal), currentRound(1), isRunning(true) {}

    // ==========================================================
    // Start() -- INVARIANT LOOP
    // Urutan fase TIDAK BOLEH berubah.
    // ==========================================================
    void Start() {
        printDivider('=');
        std::cout << "           DEICIDE -- RUN\n";
        printDivider('=');

        while (isRunning) {
            std::cout << "\n";
            printDivider();
            std::cout << " Round " << currentRound
                      << "  |  Goal: " << scoreGoal << "\n";
            printDivider();

            std::vector<std::unique_ptr<ICard>> hand, selected;

            Phase_GenerateHand(hand);                   // Phase 1
            Phase_SelectCards(hand, selected);          // Phase 2
            Phase_ApplyBonds(selected);                 // Phase 3
            int  score = Phase_ComputeScore(selected);  // Phase 4
            bool won   = Phase_EvaluateResult(score);   // Phase 5

            if (won) {
                std::cout << "\n  >> WIN  (score " << score
                          << " >= goal " << scoreGoal << ")\n";
                Phase_OpenShop();                       // Phase 6
                Phase_AdvanceRound();
            } else {
                std::cout << "\n  >> GAME OVER  (score " << score
                          << " < goal " << scoreGoal << ")\n";
                isRunning = false;
            }
        }

        std::cout << "\n";
        printDivider('=');
        std::cout << "            GAME OVER\n";
        std::cout << "        Reached Round: " << currentRound << "\n";
        printDivider('=');
    }
};
