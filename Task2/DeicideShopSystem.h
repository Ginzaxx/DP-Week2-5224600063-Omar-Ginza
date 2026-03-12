#pragma once
#include "IShopSystem.h"
#include <iostream>

// Placeholder: shop nyata menawarkan Kremnos Pack / Okhema Pack
class DeicideShopSystem : public IShopSystem {
public:
    void OpenShop() override {
        std::cout << "  [placeholder] Shop: Kremnos Pack | Okhema Pack\n";
        std::cout << "  [placeholder] Shop skipped\n";
    }
};
