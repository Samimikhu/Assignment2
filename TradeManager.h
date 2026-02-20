/*
Manages dynamic collection of BaseTrade pointers.

==========================================================
*/

#pragma once
#include "BaseTrade.h"
#include "DynamicArray.h"

class TradeManager {
private:
    //// ===== ASSIGNMENT 6 CHANGE =====
    DynamicArray<BaseTrade*> items;   // Template dynamic array
public:
    TradeManager(int cap = 5);        // default capacity
    ~TradeManager();

    void addTrade(BaseTrade* trade);
    void removeTrade(int index);
    void printAll() const;
    int getSize() const;

    // ===== ASSIGNMENT 6 ADDITIONS =====
    BaseTrade* operator[](int index) const;
    TradeManager& operator+=(BaseTrade* trade);
    TradeManager& operator-=(int index);
};
