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
    // ===== ASSIGNMENT 8 ADDITION =====
    // Private recursive helper — takes index as parameter
    void printAllRecursive(int index) const;
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
    // ===== ASSIGNMENT 8 ADDITION =====
    // Public interface — starts recursion from index 0
    void printAllRecursive() const;
};