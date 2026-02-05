#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class TradeCost {
private:
    double pricePerShare;
public:
    TradeCost() : pricePerShare(0.0) {}
    TradeCost(double p) : pricePerShare(p) {}

    void setPrice(double p) { pricePerShare = p; }
    double getPrice() const { return pricePerShare; }

    double totalValue(int shares) const {
        return pricePerShare * shares;
    }
};
