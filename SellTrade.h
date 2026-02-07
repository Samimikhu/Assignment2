#pragma once
#include "BaseTrade.h"
#include "TradeCost.h"
#include <iostream>
#include <iomanip>
using namespace std;

class SellTrade : public BaseTrade {
private:
    double profit;
    TradeCost cost;  // Composition: SellTrade "has a" TradeCost

public:
    // Default constructor
    SellTrade() {
        // Base class default constructor runs automatically
        profit = 0.0;
        // cost default constructor runs automatically
    }

    // Parameterized constructor
    SellTrade(const string& n, int s, RiskLevel r, double p, double price) {
        // Initialize base class members manually
        setName(n);
        setShares(s);
        setRisk(r);

        profit = p;
        cost.setPrice(price);
    }

    void setProfit(double p) {
        profit = p;
    }

    double getProfit() const {
        return profit;
    }

    // Setter for price (via composition)
    void setPrice(double p) {
        cost.setPrice(p);
    }

    // Getter for price (via composition)
    double getPrice() const {
        return cost.getPrice();
    }

    // Print function — adds SellTrade info on top of BaseTrade info
    void print() const {
        // Print base class info
        printBase();

        // Print SellTrade-specific info
        cout << ", Profit: $" << fixed << setprecision(2) << profit
            << ", Total Value: $" << fixed << setprecision(2)
            << cost.totalValue(getShares()) + profit << endl;
    }
};
