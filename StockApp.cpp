#include "StockApp.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// Constructor initializes counts
StockApp::StockApp() {
    numBuy = 0;
    numSell = 0;
}

// Display welcome banner
void StockApp::displayBanner() {
    cout << "=== Welcome to Stock Tracker ===\n";
}

// Add a buy trade
void StockApp::addBuyTrade() {
    if (numBuy >= MAX_TRADES) {
        cout << "Max buy trades reached!\n";
        return;
    }

    string symbol;
    int shares;
    double price, commission;
    int r;

    cin.ignore();  // Clear input buffer

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

    // Create BuyTrade object and add to array
    BuyTrade bt(symbol, shares, risk, commission, price);
    buyTrades[numBuy] = bt;
    numBuy++;

    // Save trade to file
    ofstream file("buy_trades.txt", ios::app);
    if (file) {
        file << symbol << " " << shares << " " << price << " " << commission << " " << r << endl;
        file.close();
        cout << "Buy trade saved to buy_trades.txt\n";
    }
}

// Add a sell trade
void StockApp::addSellTrade() {
    if (numSell >= MAX_TRADES) {
        cout << "Max sell trades reached!\n";
        return;
    }

    string symbol;
    int shares;
    double price, profit;
    int r;

    cin.ignore();  // Clear input buffer

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

    // Create SellTrade object and add to array
    SellTrade st(symbol, shares, risk, profit, price);
    sellTrades[numSell] = st;
    numSell++;

    // Save trade to file
    ofstream file("sell_trades.txt", ios::app);
    if (file) {
        file << symbol << " " << shares << " " << price << " " << profit << " " << r << endl;
        file.close();
        cout << "Sell trade saved to sell_trades.txt\n";
    }
}

// Display all trades and summary
void StockApp::displaySummary() {
    cout << "\n=== Buy Trades ===\n";
    for (int i = 0; i < numBuy; i++) {
        buyTrades[i].print();
    }

    cout << "\n=== Sell Trades ===\n";
    for (int i = 0; i < numSell; i++) {
        sellTrades[i].print();
    }
}

// Show menu and handle user choices
void StockApp::showMenu() {
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Buy Trade\n";
        cout << "2. Add Sell Trade\n";
        cout << "3. View Summary\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid. Enter 1-4: ";
            cin >> choice;
        }

        switch (choice) {
        case 1:
            addBuyTrade();
            break;
        case 2:
            addSellTrade();
            break;
        case 3:
            displaySummary();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        }

    } while (choice != 4);
}
