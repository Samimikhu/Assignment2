/*
Manages dynamic collection of BaseTrade pointers.

==========================================================
*/

#pragma once
#include "BaseTrade.h"
#include "DynamicArray.h"  // use template class

class TradeManager {
private:
    //// ===== ASSIGNMENT 5 ADDITION =====
    DynamicArray<BaseTrade*> items;   // replace raw array with template
public:
    TradeManager(int cap = 5) : items(cap) {}
    ~TradeManager();

    void addTrade(BaseTrade* trade);
    void removeTrade(int index);
    void printAll() const;
    int getSize() const;

    // ===== ASSIGNMENT 6 ADDITIONS =====
    BaseTrade* operator[](int index) const;  // const-correct
    TradeManager& operator+=(BaseTrade* trade);
    TradeManager& operator-=(int index);
};
