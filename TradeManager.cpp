#include "TradeManager.h"
#include <iostream>
using namespace std;

// Constructor
TradeManager::TradeManager(int cap) : items(cap) {}

// Destructor
TradeManager::~TradeManager() {
    for (int i = 0; i < items.getSize(); i++) {
        delete items[i];  // delete each dynamically allocated BaseTrade
    }
}

// Add a trade 
void TradeManager::addTrade(BaseTrade* trade) {
    items.add(trade);
}

// Remove a trade
void TradeManager::removeTrade(int index) {
    if (index < 0 || index >= items.getSize()) {
        cout << "Invalid index.\n";
        return;
    }

    delete items[index]; // free memory
    items.remove(index); // shift left automatically
}

// Print all trades (polymorphic call)
void TradeManager::printAll() const {
    for (int i = 0; i < items.getSize(); i++) {
        items[i]->print();
    }
}

int TradeManager::getSize() const {
    return items.getSize();
}

// ===== ASSIGNMENT 6 ADDITIONS =====

// operator[] with bounds checking
BaseTrade* TradeManager::operator[](int index) const {
    if (index < 0 || index >= items.getSize()) {
        cout << "Index out of bounds!\n";
        return nullptr;
    }
    return items[index];
}

// operator+= adds a trade pointer
TradeManager& TradeManager::operator+=(BaseTrade* trade) {
    addTrade(trade);
    return *this;      // allow chaining
}

// operator-= removes by index
TradeManager& TradeManager::operator-=(int index) {
    removeTrade(index);
    return *this;      // allow chaining
}
