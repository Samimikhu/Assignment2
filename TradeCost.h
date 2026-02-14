/*
Composition class used inside BuyTrade and SellTrade.

Assignment 5:
- Added as composition to separate price logic
==========================================================
*/

#pragma once

class TradeCost {
private:
    double pricePerShare;

public:
    TradeCost() : pricePerShare(0.0) {}
    TradeCost(double p) : pricePerShare(p) {}

    void setPrice(double p) { pricePerShare = p; }
    double getPrice() const { return pricePerShare; }

    // Calculates total value based on shares
    double totalValue(int shares) const {
        return pricePerShare * shares;
    }
};
