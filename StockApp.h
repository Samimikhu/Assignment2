#pragma once
#include "BuyTrade.h"
#include "SellTrade.h"
using namespace std;

class StockApp {
private:
    static const int MAX_TRADES = 10;
    BuyTrade buyTrades[MAX_TRADES];
    int numBuy;
    SellTrade sellTrades[MAX_TRADES];
    int numSell;
public:
    StockApp();
    void displayBanner();
    void addBuyTrade();
    void addSellTrade();
    void displaySummary();
    void showMenu();
};
