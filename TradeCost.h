#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class TradeCost {
private:
    double pricePerShare;

public:
    // Default constructor
    TradeCost() {
        pricePerShare = 0.0;
    }

    // Parameterized constructor
    TradeCost(double p) {
        pricePerShare = p;
    }

    // Setter for pricePerShare
    void setPrice(double p) {
        pricePerShare = p;
    }

    // Getter for pricePerShare
    double getPrice() const {
        return pricePerShare;
    }

    // Calculate total value given number of shares
    double totalValue(int shares) const {
        return pricePerShare * shares;
    }
};
