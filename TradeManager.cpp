#include "TradeManager.h"
#include <iostream>
using namespace std;

// Constructor
TradeManager::TradeManager(int cap) {
    capacity = cap;
    size = 0;
    items = new BaseTrade * [capacity];
}

// Destructor
TradeManager::~TradeManager() {
    for (int i = 0; i < size; i++) {
        delete items[i];  // delete each dynamically allocated BaseTrade
    }
    delete[] items;       // delete the array itself
}

// Resize array
void TradeManager::resize() {
    capacity *= 2;
    BaseTrade** newArray = new BaseTrade * [capacity];

    for (int i = 0; i < size; i++) {
        newArray[i] = items[i];
    }

    delete[] items;
    items = newArray;
}

// Add a trade
void TradeManager::addTrade(BaseTrade* trade) {
    if (size == capacity) {
        resize();
    }
    items[size] = trade;
    size++;
}

// Remove a trade
void TradeManager::removeTrade(int index) {  
    if (index < 0 || index >= size) {
        cout << "Invalid index.\n";
        return;
    }

    delete items[index];  // free memory

    // shift left
    for (int i = index; i < size - 1; i++) {
        items[i] = items[i + 1];
    }
    size--;
}

// Print all trades (polymorphic call)
void TradeManager::printAll() const {
    for (int i = 0; i < size; i++) {
        items[i]->print(); // calls derived print() at runtime
    }
}

int TradeManager::getSize() const {
    return size;
}
