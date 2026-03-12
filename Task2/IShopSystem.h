#pragma once

class IShopSystem {
public:
    virtual void OpenShop() = 0;
    virtual ~IShopSystem() = default;
};
