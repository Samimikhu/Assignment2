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
#include <iomanip>
using namespace std;

class SellTrade : public BaseTrade {
private:
    double profit;
    TradeCost cost;

public:
    SellTrade() : profit(0.0) {}
    SellTrade(const string& n, int s, RiskLevel r, double p, double price) {
        setName(n);
        setShares(s);
        setRisk(r);
        profit = p;
        cost.setPrice(price);
    }

    void setProfit(double p) { profit = p; }
    double getProfit() const { return profit; }

    void setPrice(double p) { cost.setPrice(p); }
    double getPrice() const { return cost.getPrice(); }

    void print() const override {
        printBase();
        cout << ", Profit: $" << fixed << setprecision(2) << profit
            << ", Total Value: $" << fixed << setprecision(2)
            << cost.totalValue(getShares()) + profit << endl;
    }

    void toStream(ostream& os) const override {
        os << "[SELL] ";
        printBase();
        os << ", Profit: $" << fixed << setprecision(2) << profit
            << ", Total Value: $" << fixed << setprecision(2)
            << cost.totalValue(getShares()) + profit;
    }
};
