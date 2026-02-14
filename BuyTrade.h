/*
Derived class from BaseTrade representing buy trades.

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

class BuyTrade : public BaseTrade {
private:
    double commission;

    //// ===== ASSIGNMENT 5 ADDITION =====
    TradeCost cost;   // Composition

public:
    BuyTrade() : BaseTrade(), commission(0.0), cost(0.0) {}

    BuyTrade(string n, int s, RiskLevel r, double c, double price)
        : BaseTrade(n, s, r), commission(c), cost(price) {
    }

    void setCommission(double c) { commission = c; }
    double getCommission() const { return commission; }

    void setPrice(double p) { cost.setPrice(p); }
    double getPrice() const { return cost.getPrice(); }

    //// ===== ASSIGNMENT 5 ADDITION =====
    // Overridden virtual function
    void print() const override {
        cout << "[BUY] "
            << name << " | Shares: " << shares
            << " | Price: $" << cost.getPrice()
            << " | Commission: $" << commission
            << endl;
    }
};
