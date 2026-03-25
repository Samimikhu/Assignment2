/*
Manages dynamic collection of BaseTrade pointers.
==========================================================
*/
#pragma once
#include "BaseTrade.h"
#include "DynamicArray.h"
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
};