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

    // ===== ASSIGNMENT 10 ADDITION =====
    void displayLinkedList();

    // ===== ASSIGNMENT 12 ADDITIONS =====
    void lookupTradeBySymbol();
    void deleteTradeFromMap();
    void displayTradeMap();

    void showMenu();
};