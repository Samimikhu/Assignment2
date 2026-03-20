#pragma once
#include <iostream>
#include <vector>
#include "BaseTrade.h"
using namespace std;

// ===== ASSIGNMENT 6 FUNCTION TEMPLATE =====
template <typename T>
T calculateTotal(T price, T quantity) {
    return price * quantity;
}

//// ===== ASSIGNMENT 6 TEMPLATE CLASS =====
// ===== ASSIGNMENT 9 CHANGE =====
// Replaced raw array (T* items) with std::vector<T>
// resize() removed — vector handles dynamic resizing automatically
template <typename T>
class DynamicArray
{
private:
    // ===== ASSIGNMENT 9 CHANGE =====
    // std::vector replaces raw array, size, and capacity variables
    vector<T> items;
public:
    DynamicArray(int cap = 4)
    {
        // ===== ASSIGNMENT 9 CHANGE =====
        // reserve() pre-allocates memory like capacity did before
        items.reserve(cap);
    }
    ~DynamicArray()
    {
        // ===== ASSIGNMENT 9 CHANGE =====
        // vector destructor handles memory automatically — no delete[] needed
    }
    void add(T item)
    {
        // ===== ASSIGNMENT 9 CHANGE =====
        // push_back() replaces manual resize and items[size++] = item
        items.push_back(item);
    }
    void remove(int index)
    {
        // ===== ASSIGNMENT 7 CHANGE =====
        // Now throws TradeException instead of silently returning on invalid index
        if (index < 0 || index >= (int)items.size())
            throw TradeException("DynamicArray: invalid removal index");
        // ===== ASSIGNMENT 9 CHANGE =====
        // erase() replaces manual shift loop — vector handles shifting automatically
        items.erase(items.begin() + index);
    }
    T& operator[](int index)
    {
        // ===== ASSIGNMENT 7 CHANGE =====
        // Now throws TradeException instead of returning dummy value on invalid index
        if (index < 0 || index >= (int)items.size())
            throw TradeException("DynamicArray: index out of bounds");
        // ===== ASSIGNMENT 9 CHANGE =====
        // .at() used for bounds-safe access
        return items.at(index);
    }
    const T& operator[](int index) const  // const-safe version
    {
        // ===== ASSIGNMENT 7 CHANGE =====
        // Const version also throws TradeException on invalid index
        if (index < 0 || index >= (int)items.size())
            throw TradeException("DynamicArray: index out of bounds");
        // ===== ASSIGNMENT 9 CHANGE =====
        // .at() used for bounds-safe access
        return items.at(index);
    }
    int getSize() const
    {
        // ===== ASSIGNMENT 9 CHANGE =====
        // .size() replaces manual size variable
        return (int)items.size();
    }
};