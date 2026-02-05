#pragma once
#include "BaseTrade.h"
#include "TradeCost.h"
using namespace std;

class BuyTrade : public BaseTrade {
private:
    double commission;
    TradeCost cost;  // composition
public:
    BuyTrade() : BaseTrade(), commission(0.0), cost() {}
    BuyTrade(const string& n, int s, RiskLevel r, double c, double price)
        : BaseTrade(n, s, r), commission(c), cost(price) {
    }

    void setCommission(double c) { commission = c; }
    double getCommission() const { return commission; }

    void setPrice(double p) { cost.setPrice(p); }
    double getPrice() const { return cost.getPrice(); }

    // Print function (redefines base behavior)
    void print() const {
        printBase();  // call base print manually
        cout << ", Commission: $" << fixed << setprecision(2) << commission
            << ", Total Cost: $" << fixed << setprecision(2)
            << cost.totalValue(shares) + commission << endl;
    }
};
