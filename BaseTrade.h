/*
Abstract base class for BuyTrade and SellTrade.

Assignment 5 ADDITIONS:
- Converted to ABSTRACT CLASS
- Added pure virtual function print()
- Added virtual destructor for polymorphism
==========================================================
*/

#pragma once
#include <string>
#include "trade.h"
using namespace std;

class BaseTrade {
protected:
    string name;
    int shares;
    RiskLevel risk;

public:
    BaseTrade() : name(""), shares(0), risk(Low) {}
    BaseTrade(string n, int s, RiskLevel r)
        : name(n), shares(s), risk(r) {
    }

    //// ===== ASSIGNMENT 5 ADDITION =====
    // Virtual destructor required for base class pointers
    virtual ~BaseTrade() {}

    // Setters
    void setName(string n) { name = n; }
    void setShares(int s) { shares = s; }
    void setRisk(RiskLevel r) { risk = r; }

    // Getters
    string getName() const { return name; }
    int getShares() const { return shares; }
    RiskLevel getRisk() const { return risk; }

    //// ===== ASSIGNMENT 5 ADDITION =====
    // Pure virtual function makes this an abstract class
    virtual void print() const = 0;
};
