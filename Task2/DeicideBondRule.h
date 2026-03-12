#pragma once
#include "IBondRule.h"
#include <iostream>
#include <string>

// ============================================================
// DeicideBondRule -- Placeholder demonstrasi cara kerja bond
//
// Karena ini skeletal, kartu di-inject langsung dari sini.
// Cara kerja bond DITUNJUKKAN secara scripted:
//   1. Deteksi kombinasi kartu yang ada
//   2. Cetak bond yang aktif
//   3. Terapkan buff ke Journey/Cycle kartu yang relevan
//
// Di implementasi penuh: kartu berasal dari Deck,
// tiap bond adalah class terpisah yang di-inject via main.cpp
// ============================================================

static bool HasCard(const std::vector<std::unique_ptr<ICard>>& cards,
                    const std::string& name) {
    for (const auto& c : cards)
        if (c && c->GetName() == name) return true;
    return false;
}

class DeicideBondRule : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {

        if (cards.empty()) {
            std::cout << "  (no cards selected -- bonds skipped)\n";
            return;
        }

        bool anyBond = false;

        // --- Bond 1: HEATED RIVALRY (Kephale + Nikador) ---
        if (HasCard(cards, "Kephale") && HasCard(cards, "Nikador")) {
            anyBond = true;
            std::cout << "  [BOND] HEATED RIVALRY activated\n";
            std::cout << "         Kephale & Nikador are rivals -- each gains +100 Journey\n";
            for (const auto& c : cards) {
                if (c->GetName() == "Kephale" || c->GetName() == "Nikador") {
                    int old = c->GetJourney();
                    c->SetJourney(old + 100);
                    std::cout << "         " << c->GetName()
                              << " Journey: " << old << " -> " << c->GetJourney() << "\n";
                }
            }
        }

        // --- Bond 2: TITAN FATE (>= 2 kartu: Janus/Talanton/Oronyx) ---
        int fateCount = 0;
        for (const auto& c : cards) {
            std::string n = c->GetName();
            if (n == "Janus" || n == "Talanton" || n == "Oronyx") fateCount++;
        }
        if (fateCount >= 2) {
            anyBond = true;
            int buff = fateCount * 2; // 2 Cycle per kartu faksi
            std::cout << "  [BOND] TITAN FATE activated (" << fateCount << " FATE cards)\n";
            std::cout << "         Each FATE card gains +" << buff << " Cycle\n";
            for (const auto& c : cards) {
                std::string n = c->GetName();
                if (n == "Janus" || n == "Talanton" || n == "Oronyx") {
                    int old = c->GetCycle();
                    c->SetCycle(old + buff);
                    std::cout << "         " << n
                              << " Cycle: " << old << " -> " << c->GetCycle() << "\n";
                }
            }
        }

        // --- Bond 3: CYCLE BEGINNING (Demiurge + Kephale) ---
        if (HasCard(cards, "Demiurge") && HasCard(cards, "Kephale")) {
            anyBond = true;
            std::cout << "  [BOND] CYCLE BEGINNING activated\n";
            std::cout << "         Demiurge blesses Kephale -- +500 Journey\n";
            for (const auto& c : cards) {
                if (c->GetName() == "Kephale") {
                    int old = c->GetJourney();
                    c->SetJourney(old + 500);
                    std::cout << "         Kephale Journey: " << old
                              << " -> " << c->GetJourney() << "\n";
                }
            }
        }

        if (!anyBond) {
            std::cout << "  (no bonds active for this hand)\n";
        }
    }
};
