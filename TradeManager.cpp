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
    // ===== ASSIGNMENT 7 CHANGE =====
    // Now throws TradeException instead of printing message on invalid index
    if (index < 0 || index >= items.getSize())
        throw TradeException("TradeManager: invalid removal index");
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
    // ===== ASSIGNMENT 7 CHANGE =====
    // Now throws TradeException instead of returning nullptr on invalid index
    if (index < 0 || index >= items.getSize())
        throw TradeException("TradeManager: index out of bounds");
    return items[index];
}
// operator+= adds a trade pointer
TradeManager& TradeManager::operator+=(BaseTrade* trade) {
    addTrade(trade);
    return *this;      // allow chaining
}
// operator-= removes by index
TradeManager& TradeManager::operator-=(int index) {
    // ===== ASSIGNMENT 7 CHANGE =====
    // Now throws TradeException on invalid index before attempting removal
    if (index < 0 || index >= items.getSize())
        throw TradeException("TradeManager: invalid removal index");
    removeTrade(index);
    return *this;      // allow chaining
}