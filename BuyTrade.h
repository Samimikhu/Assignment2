#pragma once
#include "BaseTrade.h"
#include "TradeCost.h"
#include <iostream>
#include <iomanip>
using namespace std;

class BuyTrade : public BaseTrade {
private:
    double commission;
    TradeCost cost;  // Composition: BuyTrade "has a" TradeCost

public:
    // Default constructor
    BuyTrade() {
        // Call base default constructor automatically
        commission = 0.0;
        // cost default constructor runs automatically
    }

    // Constructor with parameters
    BuyTrade(const string& n, int s, RiskLevel r, double c, double price) {
        // Initialize base class members manually
        setName(n);
        setShares(s);
        setRisk(r);

        commission = c;
        cost.setPrice(price);
    }

    void setCommission(double c) {
        commission = c;
    }

    double getCommission() const {
        return commission;
    }

    // Setter for price (via composition)
    void setPrice(double p) {
        cost.setPrice(p);
    }

    // Getter for price (via composition)
    double getPrice() const {
        return cost.getPrice();
    }

    // Print function — adds BuyTrade info on top of BaseTrade info
    void print() const {
        // Print base class info
        printBase();

        // Print BuyTrade-specific info
        cout << ", Commission: $" << fixed << setprecision(2) << commission
            << ", Total Cost: $" << fixed << setprecision(2)
            << cost.totalValue(getShares()) + commission << endl;
    }
};
