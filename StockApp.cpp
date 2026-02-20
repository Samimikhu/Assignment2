/*
Implements menu system and trade input.

Assignment 5:
- Dynamically creates trades using new
- Stores them in TradeManager
- Added full input validation to prevent invalid trades

Assignment 6:
- Uses overloaded operators instead of direct function calls
- Demonstrates template usage (removed multiply template to fix build)
==========================================================
*/

#include "StockApp.h"
#include "BuyTrade.h"
#include "SellTrade.h"
#include "TradeManager.h"
#include "DynamicArray.h"
#include <iostream>
using namespace std;

StockApp::StockApp() {}

void StockApp::displayBanner() {
    cout << "=== Stock Trading Application ===\n";
}

void StockApp::addBuyTrade() {

    string symbol;
    int shares;
    double price, commission;
    int r;

    cin.ignore(10000, '\n');

    cout << "Symbol: ";
    getline(cin, symbol);

    if (symbol.empty()) {
        cout << "Invalid symbol.\n";
        return;
    }

    cout << "Shares: ";
    if (!(cin >> shares)) {
        cout << "Invalid input for shares.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (shares <= 0) {
        cout << "Shares must be positive.\n";
        return;
    }

    cout << "Price: ";
    if (!(cin >> price)) {
        cout << "Invalid input for price.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (price <= 0) {
        cout << "Price must be positive.\n";
        return;
    }

    cout << "Risk (1=Low,2=Medium,3=High): ";
    if (!(cin >> r)) {
        cout << "Invalid input for risk.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (r < 1 || r > 3) {
        cout << "Risk must be 1, 2, or 3.\n";
        return;
    }

    cout << "Commission: ";
    if (!(cin >> commission)) {
        cout << "Invalid input for commission.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (commission < 0) {
        cout << "Commission cannot be negative.\n";
        return;
    }

    RiskLevel risk = static_cast<RiskLevel>(r - 1);

    //// ===== ASSIGNMENT 5 ADDITION =====
    BaseTrade* trade = new BuyTrade(symbol, shares, risk, commission, price);

    //// ===== ASSIGNMENT 6 CHANGE =====
    manager += trade;

    cout << "Buy trade added successfully.\n";

    //// ===== ASSIGNMENT 6 TEMPLATE USAGE =====
    double totalCost = calculateTotal<double>(price, (double)shares) + commission;
    cout << "Calculated total cost: $" << totalCost << endl;
}

void StockApp::addSellTrade() {

    string symbol;
    int shares;
    double price, profit;
    int r;

    cin.ignore(10000, '\n');

    cout << "Symbol: ";
    getline(cin, symbol);

    if (symbol.empty()) {
        cout << "Invalid symbol.\n";
        return;
    }

    cout << "Shares: ";
    if (!(cin >> shares)) {
        cout << "Invalid input for shares.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (shares <= 0) {
        cout << "Shares must be positive.\n";
        return;
    }

    cout << "Price: ";
    if (!(cin >> price)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input for price.\n";
        return;
    }

    if (price <= 0) {
        cout << "Price must be positive.\n";
        return;
    }

    cout << "Risk (1=Low,2=Medium,3=High): ";
    if (!(cin >> r)) {
        cout << "Invalid input for risk.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (r < 1 || r > 3) {
        cout << "Risk must be 1, 2, or 3.\n";
        return;
    }

    cout << "Profit: ";
    if (!(cin >> profit)) {
        cout << "Invalid input for profit.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    RiskLevel risk = static_cast<RiskLevel>(r - 1);

    //// ===== ASSIGNMENT 5 ADDITION =====
    BaseTrade* trade = new SellTrade(symbol, shares, risk, profit, price);

    //// ===== ASSIGNMENT 6 CHANGE =====
    manager += trade;

    cout << "Sell trade added successfully.\n";

    //// ===== ASSIGNMENT 6 TEMPLATE USAGE =====
    double totalValue = calculateTotal<double>(price, (double)shares) + profit;
    cout << "Calculated total value: $" << totalValue << endl;
}

void StockApp::removeTrade()
{
    if (manager.getSize() == 0) {
        cout << "No trades to remove.\n";
        return;
    }

    int index;

    cout << "Enter index to remove: ";

    if (!(cin >> index)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    //// ===== ASSIGNMENT 6 CHANGE =====
    manager -= index;
}

void StockApp::displaySummary() {

    //// ===== ASSIGNMENT 6 CHANGE =====
    //// Demonstrates operator[] and operator<< usage

    if (manager.getSize() == 0) {
        cout << "No trades recorded.\n";
        return;
    }

    for (int i = 0; i < manager.getSize(); i++) {
        BaseTrade* t = manager[i];   // operator[] used here
        if (t != nullptr)
            cout << *t << endl;      // operator<< used here
    }
}

void StockApp::showMenu()
{
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Buy Trade\n";
        cout << "2. Add Sell Trade\n";
        cout << "3. Remove Trade\n";
        cout << "4. View Summary\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            addBuyTrade();
            break;
        case 2:
            addSellTrade();
            break;
        case 3:
            removeTrade();
            break;
        case 4:
            displaySummary();
            break;
        case 5:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please select 1-5.\n";
        }

    } while (choice != 5);
}