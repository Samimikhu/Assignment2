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
// ===== ASSIGNMENT 8 ADDITIONS =====
// Private recursive helper function
// BASE CASE: index reaches end of list — stop recursion
// RECURSIVE CASE: print current trade then call self with next index
void TradeManager::printAllRecursive(int index) const {
    // BASE CASE — no more trades to print, stop recursion
    if (index >= items.getSize())
        return;
    // print current trade using polymorphic print()
    items[index]->print();
    // RECURSIVE CASE — call self with next index
    printAllRecursive(index + 1);
}
// Public interface — starts recursion from index 0
void TradeManager::printAllRecursive() const {
    printAllRecursive(0);
}
// ===== ASSIGNMENT 9 ADDITIONS =====
// Sequential search — searches element by element from beginning
// Returns index of first trade with matching name or -1 if not found
int TradeManager::sequentialSearch(const string& name) const {
    for (int i = 0; i < items.getSize(); i++) {
        if (items[i]->getName() == name)
            return i;  // found — return index
    }
    return -1;  // not found
}
// Bubble sort — sorts trades alphabetically by name
// Repeatedly compares adjacent trades and swaps if out of order
void TradeManager::bubbleSort() {
    int n = items.getSize();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // compare adjacent trades by name
            if (items[j]->getName() > items[j + 1]->getName()) {
                // swap pointers
                BaseTrade* temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}
// Binary search — searches sorted vector using low/mid/high approach
// MUST call bubbleSort() before calling this function
// Returns index of trade with matching name or -1 if not found
int TradeManager::binarySearch(const string& name) const {
    int low = 0;
    int high = items.getSize() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;  // find middle index
        if (items[mid]->getName() == name)
            return mid;   // found — return index
        else if (items[mid]->getName() < name)
            low = mid + 1;   // search right half
        else
            high = mid - 1;  // search left half
    }
    return -1;  // not found
}
// ===== ASSIGNMENT 10 ADDITIONS =====
// Insert trade at front of linked list
void TradeManager::insertFront(BaseTrade* trade) {
    tradeList.insertFront(trade);
}
// Insert trade at back of linked list
void TradeManager::insertBack(BaseTrade* trade) {
    tradeList.insertBack(trade);
}
// Delete trade from linked list by name
bool TradeManager::deleteFromList(const string& name) {
    return tradeList.deleteNode(name);
}
// Search linked list by name
BaseTrade* TradeManager::searchList(const string& name) const {
    return tradeList.search(name);
}
// Print linked list using iterator
// ===== ASSIGNMENT 10 ADDITION =====
// Uses TradeListIterator to traverse the linked list
void TradeManager::printList() const {
    cout << "\n--- Linked List Trades ---\n";
    TradeListIterator it(tradeList);  // initialize iterator to front of list
    if (!it.hasNext()) {
        cout << "No trades in linked list.\n";
        return;
    }
    while (it.hasNext()) {           // keep going while there are more nodes
        it.getData()->print();       // print current node's trade
        it.next();                   // advance to next node
    }
}
// Returns size of linked list
int TradeManager::getListSize() const {
    return tradeList.getSize();
}