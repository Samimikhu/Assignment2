/*
Abstract base class for BuyTrade and SellTrade.

Assignment 5 ADDITIONS:
- Converted to ABSTRACT CLASS
- Added pure virtual function print()
- Added virtual destructor for polymorphism
==========================================================
*/

#pragma once
#include <iostream>
#include "Trade.h"
using namespace std;

class BaseTrade {
protected:
    int shares;
private:
    string name;
    RiskLevel risk;

public:
    BaseTrade() : name(""), shares(0), risk(Low) {}
    BaseTrade(const string& n, int s, RiskLevel r) : name(n), shares(s), risk(r) {}

    void setName(const string& n) { name = n; }
    string getName() const { return name; }

    void setShares(int s) { shares = s; }
    int getShares() const { return shares; }

    void setRisk(RiskLevel r) { risk = r; }
    RiskLevel getRisk() const { return risk; }

    // Print base info
    void printBase() const {
        cout << "Trade: " << name << ", Shares: " << shares << ", Risk: ";
        switch (risk) {
        case Low: cout << "Low"; break;
        case Medium: cout << "Medium"; break;
        case High: cout << "High"; break;
        }
    }

    // ===== ASSIGNMENT 6 ADDITION =====
    virtual void print() const = 0;             // pure virtual function
    virtual void toStream(ostream& os) const = 0; // for operator<<

    virtual ~BaseTrade() {}                     

    // Operator<< overload
    friend ostream& operator<<(ostream& os, const BaseTrade& trade) {
        trade.toStream(os);
        return os;
    }
};
