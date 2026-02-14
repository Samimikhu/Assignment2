/*
==========================================================
File: SellTrade.h
Description:
Derived class from BaseTrade representing sell trades.

Assignment 5 ADDITIONS:
- Inherits from BaseTrade
- Implements overridden print()
- Uses TradeCost (composition)
==========================================================
*/

#pragma once
#include "BaseTrade.h"
#include "TradeCost.h"
#include <iostream>
using namespace std;

class SellTrade : public BaseTrade {
private:
    double profit;

    //// ===== ASSIGNMENT 5 ADDITION =====
    TradeCost cost;   // Composition

public:
    SellTrade() : BaseTrade(), profit(0.0), cost(0.0) {}

    SellTrade(string n, int s, RiskLevel r, double p, double price)
        : BaseTrade(n, s, r), profit(p), cost(price) {
    }

    void setProfit(double p) { profit = p; }
    double getProfit() const { return profit; }

    void setPrice(double p) { cost.setPrice(p); }
    double getPrice() const { return cost.getPrice(); }

    //// ===== ASSIGNMENT 5 ADDITION =====
    void print() const override {
        cout << "[SELL] "
            << name << " | Shares: " << shares
            << " | Price: $" << cost.getPrice()
            << " | Profit: $" << profit
            << endl;
    }
};
