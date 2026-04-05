/*
Abstract base class for BuyTrade and SellTrade.
Assignment 5 ADDITIONS:
- Converted to ABSTRACT CLASS
- Added pure virtual function print()
- Added virtual destructor for polymorphism
Assignment 7 ADDITIONS:
- Added custom TradeException class
Assignment 10 ADDITIONS:
- Added Node structure for linked list
- Added TradeLinkedList class
- Added TradeListIterator class
==========================================================
*/
#pragma once
#include <iostream>
#include <exception>
#include "Trade.h"
using namespace std;

// ===== ASSIGNMENT 7 ADDITION =====
// Custom exception class specific to the trading program
// Derives from std::exception so it works with standard C++ exception handling
class TradeException : public exception {
private:
    string message;  // stores the error message
public:
    // Constructor takes an error message and stores it
    TradeException(const string& msg) : message(msg) {}
    // Overrides what() from std::exception to return our custom message
    // noexcept means this function itself will never throw
    const char* what() const noexcept override {
        return message.c_str();  // convert string to const char*
    }
};

// ===== BaseTrade defined FIRST =====
// TradeNode, TradeLinkedList, and TradeListIterator are defined AFTER
// because they call getName() and print() on BaseTrade* pointers
// and the compiler needs the full BaseTrade definition for that
class BaseTrade {
protected:
    int shares;
private:
    string name;
    RiskLevel risk;
public:
    BaseTrade() : name(""), shares(0), risk(Low) {}
    BaseTrade(const string& n, int s, RiskLevel r) : name(n), shares(s), risk(r) {}
    void setName(const string& n) { name = n; }
    string getName() const { return name; }
    void setShares(int s) { shares = s; }
    int getShares() const { return shares; }
    void setRisk(RiskLevel r) { risk = r; }
    RiskLevel getRisk() const { return risk; }
    // Print base info
    void printBase() const {
        cout << "Trade: " << name << ", Shares: " << shares << ", Risk: ";
        switch (risk) {
        case Low: cout << "Low"; break;
        case Medium: cout << "Medium"; break;
        case High: cout << "High"; break;
        }
    }
    // ===== ASSIGNMENT 6 ADDITION =====
    virtual void print() const = 0;               // pure virtual function
    virtual void toStream(ostream& os) const = 0; // for operator
    virtual ~BaseTrade() {}
    // Operator<< overload
    friend ostream& operator<<(ostream& os, const BaseTrade& trade) {
        trade.toStream(os);
        return os;
    }
};

// ===== ASSIGNMENT 10 ADDITION =====
// Node structure for the linked list
// Defined AFTER BaseTrade so compiler knows what BaseTrade* is
struct TradeNode {
    BaseTrade* data;      // the trade stored in this node
    TradeNode* next;      // pointer to the next node in the list
    // Constructor � initializes data and sets next to nullptr
    TradeNode(BaseTrade* trade) : data(trade), next(nullptr) {}
};

// ===== ASSIGNMENT 11 ADDITION =====
// Stack and Queue classes using TradeNode

class TradeStack {
    private:
        TradeNode* stackTop; // pointer to the top of the stack
        int size; // number of elements in the stack
    
    public:
        // Constructor for TradeStack
        TradeStack(){
            stackTop = nullptr;
            size = 0;
        }
        // Intializes the stack
        void initializeTradeStack() {
            TradeNode* temp;
            while(stackTop != nullptr){
                temp = stackTop;
                stackTop = stackTop->next;
                delete temp; 
            }

        }
        // Destructor for TradeStack
        ~TradeStack() {
            initializeTradeStack();
        }

        // Pushes a trade onto the stack
        void push(BaseTrade* trade){
            TradeNode* newNode = new TradeNode(trade);

            newNode->next = stackTop;
            stackTop = newNode;
            
            size++;
        }

        // Pops a trade from the stack
        void pop() {
            TradeNode* temp;

            if (stackTop != nullptr){
                temp = stackTop;
                stackTop = stackTop->next;
                delete temp;
                size--;
            }
            else {
                cout << "Cannot remove from an empty stack." << endl;
            }
        }

        // Return the top trade on the stack
        BaseTrade* top() const {
            if (stackTop != nullptr){
                return stackTop->data;
            }
            else{
                cout << "Stack is empty." << endl;
                return nullptr;
            }
        }

        // Check if the stack is empty
        bool isEmptyTradeStack() const {
            return stackTop == nullptr;
        }
        // Returns the size of the stack
        int getStackSize() const {
            return size;
        }
};

// First in, first out
class TradeQueue {
    private:
        TradeNode* front; // front of the queue
        TradeNode* rear; // rear/back of the queue
        int size; // number of elements in the queue
    
    public:
        // Constructor for TradeQueue
        TradeQueue() {
            front = nullptr;
            rear = nullptr;
            size = 0;
        }

        // Initializes the queue
        void initializeTradeQueue() {
            TradeNode* temp;
            while (front != nullptr){
                temp = front;
                front = front->next;
                delete temp;
            }
            rear = nullptr; // making sure rear is also nullptr
            size = 0;
        }

        // Destructor for TradeQueue
        ~TradeQueue() {
            initializeTradeQueue();
        }

        // Enqueues a trade to the rear of the queue
        void enqueueTrade(BaseTrade* trade){
            TradeNode* newNode;
            newNode = new TradeNode(trade);
            newNode->next = nullptr;
            
            if (front == nullptr){
                front = newNode;
                rear = newNode;
            } else{
                rear->next = newNode;
                rear = rear->next;
            }
        }

        // CHeck if the queue is empty
        bool isEmptyTradeQueue() const {
            return front == nullptr;
        }

        // Dequeues a trade from the front of the queue
        void dequeueTrade() {
            TradeNode* temp;

            if(!isEmptyTradeQueue()){
                temp = front;

                front = front->next;

                delete temp;

                size--;

                if (front == nullptr){ // if the queue becomes empty after dequeueing
                    rear = nullptr; 
                }
            }
        }
        // Returns the size of the queue
        int getQueueSize() const {
            return size;
        }

        // Returns the front of the trade queue

        BaseTrade* frontTrade() const {
            if (!isEmptyTradeQueue()){
                return front->data;
            } else {
                cout << "Queue is empty." << endl;
                return nullptr;
            }
        }
};


// ===== ASSIGNMENT 10 ADDITION =====
// Unordered linked list of trades
// Insertions can be at the front or back
// This is an unordered list � trades are stored in insertion order
class TradeLinkedList {
private:
    TradeNode* head;  // pointer to first node
    TradeNode* tail;  // pointer to last node
    int size;         // number of nodes in the list
public:
    // Constructor � initializes empty list
    TradeLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    // Destructor � deletes all nodes to prevent memory leaks
    ~TradeLinkedList() {
        TradeNode* current = head;
        while (current != nullptr) {
            TradeNode* next = current->next;
            delete current;  // delete the node (not the trade � TradeManager owns trades)
            current = next;
        }
    }
    // Insert at front � adds new node at the beginning of the list
    void insertFront(BaseTrade* trade) {
        TradeNode* newNode = new TradeNode(trade);
        if (head == nullptr) {
            // list is empty � new node is both head and tail
            head = newNode;
            tail = newNode;
        }
        else {
            // point new node to current head then update head
            newNode->next = head;
            head = newNode;
        }
        size++;
    }
    // Insert at back � adds new node at the end of the list
    void insertBack(BaseTrade* trade) {
        TradeNode* newNode = new TradeNode(trade);
        if (tail == nullptr) {
            // list is empty � new node is both head and tail
            head = newNode;
            tail = newNode;
        }
        else {
            // point current tail to new node then update tail
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    // Delete � removes node with matching trade name
    // Returns true if found and deleted, false if not found
    bool deleteNode(const string& name) {
        if (head == nullptr)
            return false;  // empty list � nothing to delete
        // check if head node matches
        if (head->data->getName() == name) {
            TradeNode* temp = head;
            head = head->next;
            if (head == nullptr)
                tail = nullptr;  // list is now empty
            delete temp;
            size--;
            return true;
        }
        // search rest of list
        TradeNode* current = head;
        while (current->next != nullptr) {
            if (current->next->data->getName() == name) {
                TradeNode* temp = current->next;
                current->next = temp->next;
                if (temp == tail)
                    tail = current;  // update tail if last node deleted
                delete temp;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;  // not found
    }
    // Search � finds node with matching trade name
    // Returns pointer to trade if found, nullptr if not found
    BaseTrade* search(const string& name) const {
        TradeNode* current = head;
        while (current != nullptr) {
            if (current->data->getName() == name)
                return current->data;  // found � return trade pointer
            current = current->next;
        }
        return nullptr;  // not found
    }
    // Print/Traverse � visits and displays every node in the list
    void print() const {
        TradeNode* current = head;
        if (current == nullptr) {
            cout << "No trades in linked list.\n";
            return;
        }
        while (current != nullptr) {
            current->data->print();
            current = current->next;
        }
    }
    // Returns number of nodes in the list
    int getSize() const { return size; }
    // Returns head pointer � used by iterator
    TradeNode* getHead() const { return head; }
};

// ===== ASSIGNMENT 10 ADDITION =====
// Iterator class for TradeLinkedList
// Supports initialization to front, advancing to next, and accessing current data
class TradeListIterator {
private:
    TradeNode* current;  // pointer to current node
public:
    // Constructor � initializes iterator to front of list
    TradeListIterator(const TradeLinkedList& list) : current(list.getHead()) {}
    // Returns true if there are more nodes to visit
    bool hasNext() const { return current != nullptr; }
    // Advances iterator to next node
    void next() {
        if (current != nullptr)
            current = current->next;
    }
    // Returns data of current node
    BaseTrade* getData() const {
        if (current != nullptr)
            return current->data;
        return nullptr;
    }
};
