#pragma once
#include "BaseTrade.h"
#include "TradeCost.h"
using namespace std;

class SellTrade : public BaseTrade {
private:
    double profit;
    TradeCost cost;
public:
    SellTrade() : BaseTrade(), profit(0.0), cost() {}
    SellTrade(const string& n, int s, RiskLevel r, double p, double price)
        : BaseTrade(n, s, r), profit(p), cost(price) {
    }

    void setProfit(double p) { profit = p; }
    double getProfit() const { return profit; }

    void setPrice(double p) { cost.setPrice(p); }
    double getPrice() const { return cost.getPrice(); }

    void print() const {
        printBase(); // call base print manually
        cout << ", Profit: $" << fixed << setprecision(2) << profit
            << ", Total Value: $" << fixed << setprecision(2)
            << cost.totalValue(shares) + profit << endl;
    }
};
