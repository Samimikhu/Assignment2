/*
Main application controller.

Assignment 5:
- Now uses TradeManager instead of fixed arrays.
==========================================================
*/

#pragma once
#include "TradeManager.h"

class StockApp {
private:
    //// ===== ASSIGNMENT 5 ADDITION =====
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
