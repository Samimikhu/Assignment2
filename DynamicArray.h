#pragma once
#include <iostream>
using namespace std;

// ===== ASSIGNMENT 6 FUNCTION TEMPLATE =====
template <typename T>
T calculateTotal(T price, T quantity) {
    return price * quantity;
}

//// ===== ASSIGNMENT 6 TEMPLATE CLASS =====
template <typename T>
class DynamicArray
{
private:
    T* items;
    int size;
    int capacity;
    void resize()
    {
        capacity *= 2;
        T* newArray = new T[capacity];
        for (int i = 0; i < size; i++)
            newArray[i] = items[i];
        delete[] items;
        items = newArray;
    }
public:
    DynamicArray(int cap = 4)
    {
        capacity = cap;
        size = 0;
        items = new T[capacity];
    }
    ~DynamicArray()
    {
        delete[] items;
    }
    void add(T item)
    {
        if (size == capacity)
            resize();
        items[size++] = item;
    }
    void remove(int index)
    {
        if (index < 0 || index >= size)
            return;
        for (int i = index; i < size - 1; i++)
            items[i] = items[i + 1];
        size--;
    }
    T& operator[](int index)
    {
        static T dummy{};
        if (index < 0 || index >= size)
            return dummy;
        return items[index];
    }
    const T& operator[](int index) const  // const-safe version
    {
        static T dummy{};
        if (index < 0 || index >= size)
            return dummy;
        return items[index];
    }
    int getSize() const
    {
        return size;
    }
};