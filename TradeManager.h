/*
Manages dynamic collection of BaseTrade pointers.

==========================================================
*/

#pragma once
#include "BaseTrade.h"

class TradeManager {
private:
    //// ===== ASSIGNMENT 5 ADDITION =====
    BaseTrade** items;   // Array of base-class pointers
    int capacity;
    int size;

    void resize();

public:
    TradeManager(int cap = 5);
    ~TradeManager();

    void addTrade(BaseTrade* trade);
    void removeTrade(int index);
    void printAll() const;
    int getSize() const;
};
