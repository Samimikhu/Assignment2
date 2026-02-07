#pragma once
#include <iostream>
#include "Trade.h"
using namespace std;

// Base class for trades
class BaseTrade {
protected:
    int shares; // Derived classes can access

private:
    string name;
    RiskLevel risk;

public:
    // Default constructor
    BaseTrade() {
        name = "";
        shares = 0;
        risk = Low;
    }

    // Constructor with parameters
    BaseTrade(const string& n, int s, RiskLevel r) {
        name = n;
        shares = s;
        risk = r;
    }

    void setName(const string& n) {
        name = n;
    }

    string getName() const {
        return name;
    }

    void setShares(int s) {
        shares = s;
    }

    int getShares() const {
        return shares;
    }

    void setRisk(RiskLevel r) {
        risk = r;
    }

    RiskLevel getRisk() const {
        return risk;
    }

    // Print function for base info
    void printBase() const {
        cout << "Trade: " << name
            << ", Shares: " << shares
            << ", Risk: ";
        switch (risk) {
        case Low:
            cout << "Low";
            break;
        case Medium:
            cout << "Medium";
            break;
        case High:
            cout << "High";
            break;
        }
    }
};
