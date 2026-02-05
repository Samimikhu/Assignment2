#include "StockApp.h"
#include <iostream>
#include <iomanip>
using namespace std;

StockApp::StockApp() : numBuy(0), numSell(0) {}

void StockApp::displayBanner() {
    cout << "=== Welcome to Stock Tracker  ===\n";
}

void StockApp::addBuyTrade() {
    if (numBuy >= MAX_TRADES) {
        cout << "Max buy trades reached!\n";
        return;
    }

    string symbol;
    int shares;
    double price, commission;
    int r;

    cin.ignore();
    cout << "Enter stock symbol: ";
    getline(cin, symbol);

    cout << "Enter number of shares: ";
    cin >> shares;

    cout << "Enter price per share: ";
    cin >> price;

    cout << "Select risk (1=Low,2=Medium,3=High): ";
    cin >> r;
    RiskLevel risk = static_cast<RiskLevel>(r - 1);

    cout << "Enter commission: ";
    cin >> commission;

    buyTrades[numBuy++] = BuyTrade(symbol, shares, risk, commission, price);
}

void StockApp::addSellTrade() {
    if (numSell >= MAX_TRADES) {
        cout << "Max sell trades reached!\n";
        return;
    }

    string symbol;
    int shares;
    double price, profit;
    int r;

    cin.ignore();
    cout << "Enter stock symbol: ";
    getline(cin, symbol);

    cout << "Enter number of shares: ";
    cin >> shares;

    cout << "Enter price per share: ";
    cin >> price;

    cout << "Select risk (1=Low,2=Medium,3=High): ";
    cin >> r;
    RiskLevel risk = static_cast<RiskLevel>(r - 1);

    cout << "Enter profit: ";
    cin >> profit;

    sellTrades[numSell++] = SellTrade(symbol, shares, risk, profit, price);
}

void StockApp::displaySummary() {
    cout << "\n=== Buy Trades ===\n";
    for (int i = 0; i < numBuy; i++)
        buyTrades[i].print();

    cout << "\n=== Sell Trades ===\n";
    for (int i = 0; i < numSell; i++)
        sellTrades[i].print();
}

void StockApp::showMenu() {
    int choice;
    do {
        cout << "\nMenu:\n1. Add Buy Trade\n2. Add Sell Trade\n3. View Summary\n4. Exit\nChoice: ";
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid. Enter 1-4: ";
            cin >> choice;
        }

        switch (choice) {
        case 1: addBuyTrade(); break;
        case 2: addSellTrade(); break;
        case 3: displaySummary(); break;
        case 4: cout << "Exiting...\n"; break;
        }

    } while (choice != 4);
}
