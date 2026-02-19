/*
Main application controller.

Assignment 5:
- Now uses TradeManager instead of fixed arrays.
==========================================================
*/

/*
Header for StockApp
==========================================================
*/

#pragma once
#include "TradeManager.h"

class StockApp {
private:
    TradeManager manager;

public:
    StockApp();

    void displayBanner();
    void addBuyTrade();
    void addSellTrade();
    void removeTrade();
    void displaySummary();
    void showMenu();
};

