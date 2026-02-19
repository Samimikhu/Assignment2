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
#include <iomanip>
using namespace std;

class BuyTrade : public BaseTrade {
private:
    double commission;
    TradeCost cost;

public:
    BuyTrade() : commission(0.0) {}
    BuyTrade(const string& n, int s, RiskLevel r, double c, double price) {
        setName(n);
        setShares(s);
        setRisk(r);
        commission = c;
        cost.setPrice(price);
    }

    void setCommission(double c) { commission = c; }
    double getCommission() const { return commission; }

    void setPrice(double p) { cost.setPrice(p); }
    double getPrice() const { return cost.getPrice(); }

    void print() const override {
        printBase();
        cout << ", Commission: $" << fixed << setprecision(2) << commission
            << ", Total Cost: $" << fixed << setprecision(2)
            << cost.totalValue(getShares()) + commission << endl;
    }

    void toStream(ostream& os) const override {
        os << "[BUY] ";
        printBase();
        os << ", Commission: $" << fixed << setprecision(2) << commission
            << ", Total Cost: $" << fixed << setprecision(2)
            << cost.totalValue(getShares()) + commission;
    }

    // ===== ASSIGNMENT 6 ADDITION =====
    bool operator==(const BuyTrade& other) const {
        return getName() == other.getName() && getShares() == other.getShares();
    }
};
