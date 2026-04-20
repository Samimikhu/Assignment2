/*
Manages dynamic collection of BaseTrade pointers.

===== ASSIGNMENT 12 ADDITION =====
- Added std::map for fast symbol-based trade lookup
- Map key: stock symbol (string), Value: BaseTrade pointer
- Provides O(log n) lookup instead of O(n) sequential search
==========================================================
*/
#pragma once
#include "BaseTrade.h"
#include "DynamicArray.h"
#include <map>   // ===== ASSIGNMENT 12 ADDITION =====

class TradeManager {
private:
    //// ===== ASSIGNMENT 6 CHANGE =====
    DynamicArray<BaseTrade*> items;   // Template dynamic array

    // ===== ASSIGNMENT 8 ADDITION =====
    // Private helper for recursive print
    void printAllRecursive(int index) const;

    // ===== ASSIGNMENT 10 ADDITION =====
    // Linked list that mirrors trades for linked list operations
    TradeLinkedList tradeList;

    // ===== ASSIGNMENT 12 ADDITION =====
    // Map for fast lookup by symbol
    // Why std::map instead of DynamicArray/LinkedList:
    // - O(log n) lookup vs O(n) sequential search
    // - Automatic ordering by symbol for easy display
    // - Perfect for portfolio management where symbol lookups are frequent
    std::map<string, BaseTrade*> tradeMap;

public:
    TradeManager(int cap = 5);        // default capacity
    ~TradeManager();

    void addTrade(BaseTrade* trade);
    void removeTrade(int index);
    void printAll() const;
    int getSize() const;

    // ===== ASSIGNMENT 6 ADDITIONS =====
    BaseTrade* operator[](int index) const;
    TradeManager& operator+=(BaseTrade* trade);
    TradeManager& operator-=(int index);
    // ===== ASSIGNMENT 8 ADDITION =====
    // Public interface for recursive print
    void printAllRecursive() const;
    // ===== ASSIGNMENT 9 ADDITIONS =====
    // Sequential search — returns index of trade by name or -1 if not found
    int sequentialSearch(const string& name) const;
    // Bubble sort — sorts trades alphabetically by name
    void bubbleSort();
    // Binary search — must call bubbleSort() first, returns index or -1
    int binarySearch(const string& name) const;
    // ===== ASSIGNMENT 10 ADDITIONS =====
    // Insert trade at front of linked list
    void insertFront(BaseTrade* trade);
    // Insert trade at back of linked list
    void insertBack(BaseTrade* trade);
    // Delete trade from linked list by name
    bool deleteFromList(const string& name);
    // Search linked list by name
    BaseTrade* searchList(const string& name) const;
    // Print linked list using iterator
    void printList() const;
    // Returns size of linked list
    int getListSize() const;

    // ===== ASSIGNMENT 12 ADDITIONS =====
    // Map operations for fast symbol-based trade lookup

    // Insert — add trade to map by symbol
    void insertIntoMap(BaseTrade* trade);

    // Lookup — retrieve trade by symbol (O(log n) vs O(n) sequential search)
    BaseTrade* lookupBySymbol(const string& symbol) const;

    // Delete — remove trade from map by symbol
    bool deleteFromMap(const string& symbol);

    // Iterate — traverse and display all trades in map (alphabetically by symbol)
    void printMap() const;

    // Returns number of unique symbols in map
    int getMapSize() const;
};