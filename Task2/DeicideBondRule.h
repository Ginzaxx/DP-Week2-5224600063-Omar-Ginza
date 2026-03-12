#pragma once
#include "IBondRule.h"
#include <iostream>

// Placeholder: bond belum aktif
// Implementasi nyata: cek kombinasi kartu, buff Journey/Cycle
class DeicideBondRule : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        std::cout << "  [placeholder] No active bonds — "
                  << cards.size() << " card(s) unmodified\n";
    }
};
