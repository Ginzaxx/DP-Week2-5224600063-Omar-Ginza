#pragma once
#include "IShopSystem.h"
#include <iostream>

class DeicideShopSystem : public IShopSystem {
public:
    void OpenShop() override {
        std::cout << "  [Kremnos Pack]  upgrade Journey/Cycle kartu pilihan\n";
        std::cout << "  [Okhema Pack]   upgrade nilai buff salah satu bond\n";
        std::cout << "  (placeholder -- shop skipped)\n";
    }
};
