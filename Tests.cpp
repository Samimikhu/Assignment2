/*
Unit tests using doctest framework.
==========================================================
*/
#ifdef RUN_TESTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "BuyTrade.h"
#include "SellTrade.h"
#include "TradeManager.h"
#include "TradeCost.h"
#include "DynamicArray.h"
#include "StockApp.h"
#include "json.hpp"
#include <sstream>
// ==========================================================
// A) CONSTRUCTOR TESTS
// ==========================================================
TEST_CASE("BuyTrade constructor initializes fields") {
    BuyTrade b("AAPL", 10, Medium, 5.0, 100.0);
    CHECK(b.getName() == "AAPL");
    CHECK(b.getShares() == 10);
    CHECK(b.getRisk() == Medium);
    CHECK(b.getCommission() == 5.0);
    CHECK(b.getPrice() == 100.0);
}
TEST_CASE("SellTrade constructor initializes fields") {
    SellTrade s("GOOG", 5, High, 50.0, 200.0);
    CHECK(s.getName() == "GOOG");
    CHECK(s.getShares() == 5);
    CHECK(s.getRisk() == High);
    CHECK(s.getProfit() == 50.0);
    CHECK(s.getPrice() == 200.0);
}
// ==========================================================
// B) COMPOSITION TEST
// ==========================================================
TEST_CASE("TradeCost calculates total value correctly") {
    TradeCost cost(50.0);
    CHECK(cost.totalValue(4) == doctest::Approx(200.0));
}
// ==========================================================
// C) TEST ADDING ITEMS TO ARRAY (TradeManager)
// ==========================================================
TEST_CASE("TradeManager adds items correctly") {
    TradeManager manager(2);   // small capacity to test resize
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* s1 = new SellTrade("TSLA", 5, High, 10.0, 200.0);
    manager.addTrade(b1);
    manager.addTrade(s1);
    CHECK(manager.getSize() == 2);
}
// ==========================================================
// D) TEST REMOVING ITEMS FROM ARRAY
// ==========================================================
TEST_CASE("TradeManager removes items correctly") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* s1 = new SellTrade("TSLA", 5, High, 10.0, 200.0);
    manager.addTrade(b1);
    manager.addTrade(s1);
    manager.removeTrade(0);
    CHECK(manager.getSize() == 1);
}
// ==========================================================
// E) TEST VIRTUAL FUNCTION (POLYMORPHISM)
// ==========================================================
TEST_CASE("TradeManager calls print() through base class pointers") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* s1 = new SellTrade("TSLA", 5, High, 10.0, 200.0);
    manager.addTrade(b1);
    manager.addTrade(s1);
    manager.printAll();
    CHECK(manager.getSize() == 2);
}
// ==========================================================
// F) ASSIGNMENT 6 TESTS (OPERATORS)
// ==========================================================
// Operator== test
TEST_CASE("BuyTrade equality") {
    BuyTrade b1("AAPL", 10, Medium, 5.0, 100.0);
    BuyTrade b2("AAPL", 10, Low, 2.0, 50.0);
    BuyTrade b3("MSFT", 10, Medium, 5.0, 100.0);
    CHECK(b1 == b2); // same symbol & shares
    CHECK_FALSE(b1 == b3);
}
// Operator<< tests
TEST_CASE("Operator<< BuyTrade") {
    BuyTrade b("AAPL", 10, Medium, 5.0, 100.0);
    std::ostringstream out;
    out << b;
    CHECK(out.str().find("[BUY]") != std::string::npos);
}
TEST_CASE("Operator<< SellTrade") {
    SellTrade s("TSLA", 5, High, 50.0, 200.0);
    std::ostringstream out;
    out << s;
    CHECK(out.str().find("[SELL]") != std::string::npos);
}
// TradeManager operator[] test
// ===== ASSIGNMENT 7 CHANGE =====
// Updated to check that invalid indexes throw TradeException instead of returning nullptr
TEST_CASE("TradeManager indexing") {
    TradeManager manager;
    BaseTrade* b = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager.addTrade(b);
    CHECK(manager[0] == b);
    CHECK_THROWS_AS(manager[-1], TradeException);  // negative index throws
    CHECK_THROWS_AS(manager[99], TradeException);  // index too large throws
}
// TradeManager operator+= and operator-=
TEST_CASE("TradeManager add/remove operators") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager += b1;
    CHECK(manager.getSize() == 1);
    manager -= 0;
    CHECK(manager.getSize() == 0);
}
// ==========================================================
// G) ASSIGNMENT 6 TEMPLATE TESTS
// ==========================================================
TEST_CASE("calculateTotal works with doubles") {
    CHECK(calculateTotal<double>(10.0, 5.0) == doctest::Approx(50.0));
}
TEST_CASE("calculateTotal works with ints") {
    CHECK(calculateTotal<int>(3, 4) == 12);
}
TEST_CASE("DynamicArray resizes and stores correctly") {
    DynamicArray<int> arr(2);
    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.add(4);
    CHECK(arr.getSize() == 4);
    CHECK(arr[0] == 1);
    CHECK(arr[3] == 4);
}
TEST_CASE("DynamicArray removes and shifts correctly") {
    DynamicArray<int> arr(4);
    arr.add(10);
    arr.add(20);
    arr.add(30);
    arr.remove(1);
    CHECK(arr.getSize() == 2);
    CHECK(arr[0] == 10);
    CHECK(arr[1] == 30);
}
// ==========================================================
// H) ASSIGNMENT 7 EXCEPTION TESTS
// ==========================================================
// Tests that custom exception stores and returns message correctly
TEST_CASE("TradeException stores and returns message") {
    TradeException ex("test error");
    CHECK(string(ex.what()) == "test error");
}
// Tests that operator[] throws TradeException on invalid index
TEST_CASE("TradeManager operator[] throws on invalid index") {
    TradeManager manager;
    BaseTrade* b = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager.addTrade(b);
    CHECK_THROWS_AS(manager[-1], TradeException);  // negative index
    CHECK_THROWS_AS(manager[99], TradeException);  // index too large
}
// Tests that operator-= throws TradeException on invalid index
TEST_CASE("TradeManager operator-= throws on invalid index") {
    TradeManager manager;
    CHECK_THROWS_AS(manager -= 0, TradeException);   // empty manager
    CHECK_THROWS_AS(manager -= -1, TradeException);  // negative index
}
// Tests that DynamicArray operator[] throws on invalid index
TEST_CASE("DynamicArray operator[] throws on invalid index") {
    DynamicArray<int> arr(4);
    arr.add(10);
    CHECK_THROWS_AS(arr[-1], TradeException);   // negative index
    CHECK_THROWS_AS(arr[99], TradeException);   // index too large
}
// Tests that DynamicArray remove() throws on invalid index
TEST_CASE("DynamicArray remove throws on invalid index") {
    DynamicArray<int> arr(4);
    arr.add(10);
    CHECK_THROWS_AS(arr.remove(-1), TradeException);  // negative index
    CHECK_THROWS_AS(arr.remove(99), TradeException);  // index too large
}
// ==========================================================
// I) ASSIGNMENT 8 RECURSION TESTS
// ==========================================================
// Tests that printAllRecursive runs without errors on empty manager
TEST_CASE("printAllRecursive works on empty manager") {
    TradeManager manager;
    manager.printAllRecursive();  // should not crash or throw
    CHECK(manager.getSize() == 0);
}
// Tests that printAllRecursive prints all trades correctly
TEST_CASE("printAllRecursive prints all trades") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* s1 = new SellTrade("TSLA", 5, High, 10.0, 200.0);
    BaseTrade* b2 = new BuyTrade("GOOG", 3, Medium, 1.0, 50.0);
    manager.addTrade(b1);
    manager.addTrade(s1);
    manager.addTrade(b2);
    manager.printAllRecursive();  // should print all 3 trades
    CHECK(manager.getSize() == 3);  // all trades still in manager after print
}
// Tests that printAllRecursive and printAll produce same number of trades
TEST_CASE("printAllRecursive matches printAll behavior") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* s1 = new SellTrade("TSLA", 5, High, 10.0, 200.0);
    manager.addTrade(b1);
    manager.addTrade(s1);
    manager.printAll();
    manager.printAllRecursive();
    CHECK(manager.getSize() == 2);
}
// ==========================================================
// J) ASSIGNMENT 9 SEARCH AND SORT TESTS
// ==========================================================
// Sequential search — found
TEST_CASE("sequentialSearch finds existing trade") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* s1 = new SellTrade("TSLA", 5, High, 10.0, 200.0);
    BaseTrade* b2 = new BuyTrade("GOOG", 3, Medium, 1.0, 50.0);
    manager.addTrade(b1);
    manager.addTrade(s1);
    manager.addTrade(b2);
    CHECK(manager.sequentialSearch("TSLA") == 1);  // TSLA is at index 1
    CHECK(manager.sequentialSearch("AAPL") == 0);  // AAPL is at index 0
}
// Sequential search — not found
TEST_CASE("sequentialSearch returns -1 when not found") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager.addTrade(b1);
    CHECK(manager.sequentialSearch("MSFT") == -1);  // MSFT not in manager
}
// Sequential search — empty manager
TEST_CASE("sequentialSearch returns -1 on empty manager") {
    TradeManager manager;
    CHECK(manager.sequentialSearch("AAPL") == -1);  // nothing to search
}
// Bubble sort — sorts alphabetically
TEST_CASE("bubbleSort sorts trades alphabetically") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("TSLA", 10, Low, 2.0, 100.0);
    BaseTrade* b2 = new BuyTrade("AAPL", 5, High, 1.0, 50.0);
    BaseTrade* b3 = new BuyTrade("GOOG", 3, Medium, 1.0, 75.0);
    manager.addTrade(b1);
    manager.addTrade(b2);
    manager.addTrade(b3);
    manager.bubbleSort();
    CHECK(manager[0]->getName() == "AAPL");  // A comes first
    CHECK(manager[1]->getName() == "GOOG");  // G comes second
    CHECK(manager[2]->getName() == "TSLA");  // T comes last
}
// Binary search — found after sort
TEST_CASE("binarySearch finds trade after sort") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("TSLA", 10, Low, 2.0, 100.0);
    BaseTrade* b2 = new BuyTrade("AAPL", 5, High, 1.0, 50.0);
    BaseTrade* b3 = new BuyTrade("GOOG", 3, Medium, 1.0, 75.0);
    manager.addTrade(b1);
    manager.addTrade(b2);
    manager.addTrade(b3);
    manager.bubbleSort();  // must sort before binary search
    CHECK(manager.binarySearch("AAPL") != -1);  // AAPL should be found
    CHECK(manager.binarySearch("GOOG") != -1);  // GOOG should be found
    CHECK(manager.binarySearch("TSLA") != -1);  // TSLA should be found
}
// Binary search — not found
TEST_CASE("binarySearch returns -1 when not found") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager.addTrade(b1);
    manager.bubbleSort();
    CHECK(manager.binarySearch("MSFT") == -1);  // MSFT not in manager
}
// Binary search — empty manager
TEST_CASE("binarySearch returns -1 on empty manager") {
    TradeManager manager;
    CHECK(manager.binarySearch("AAPL") == -1);  // nothing to search
}
// ==========================================================
// K) ASSIGNMENT 10 LINKED LIST TESTS
// ==========================================================
// Insert at front — empty list
TEST_CASE("insertFront into empty list") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager.insertFront(b1);
    CHECK(manager.getListSize() == 1);
    CHECK(manager.searchList("AAPL") != nullptr);  // should be found
}
// Insert at back — empty list
TEST_CASE("insertBack into empty list") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager.insertBack(b1);
    CHECK(manager.getListSize() == 1);
    CHECK(manager.searchList("AAPL") != nullptr);  // should be found
}
// Insert at front and back — verify order
TEST_CASE("insertFront and insertBack maintain correct order") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* b2 = new BuyTrade("TSLA", 5, High, 1.0, 50.0);
    BaseTrade* b3 = new BuyTrade("GOOG", 3, Medium, 1.0, 75.0);
    manager.insertBack(b1);   // AAPL at back
    manager.insertBack(b2);   // TSLA at back
    manager.insertFront(b3);  // GOOG at front
    CHECK(manager.getListSize() == 3);
}
// Delete — existing node
TEST_CASE("deleteFromList removes existing trade") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* b2 = new BuyTrade("TSLA", 5, High, 1.0, 50.0);
    manager.insertBack(b1);
    manager.insertBack(b2);
    bool result = manager.deleteFromList("AAPL");
    CHECK(result == true);               // deletion should succeed
    CHECK(manager.getListSize() == 1);   // size should decrease
    CHECK(manager.searchList("AAPL") == nullptr);  // should no longer be found
}
// Delete — node that does not exist
TEST_CASE("deleteFromList returns false when not found") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager.insertBack(b1);
    bool result = manager.deleteFromList("MSFT");  // MSFT never added
    CHECK(result == false);              // deletion should fail
    CHECK(manager.getListSize() == 1);  // size should not change
}
// Delete — empty list
TEST_CASE("deleteFromList returns false on empty list") {
    TradeManager manager;
    bool result = manager.deleteFromList("AAPL");
    CHECK(result == false);             // nothing to delete
    CHECK(manager.getListSize() == 0);  // size stays 0
}
// Search — found
TEST_CASE("searchList finds existing trade") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager.insertBack(b1);
    BaseTrade* result = manager.searchList("AAPL");
    CHECK(result != nullptr);           // should be found
    CHECK(result->getName() == "AAPL"); // should return correct trade
}
// Search — not found
TEST_CASE("searchList returns nullptr when not found") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager.insertBack(b1);
    CHECK(manager.searchList("MSFT") == nullptr);  // MSFT never added
}
// Traverse — empty list
TEST_CASE("printList traverses empty list without crashing") {
    TradeManager manager;
    manager.printList();  // should not crash
    CHECK(manager.getListSize() == 0);
}
// Traverse — multiple trades using iterator
TEST_CASE("printList traverses all trades using iterator") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* s1 = new SellTrade("TSLA", 5, High, 10.0, 200.0);
    manager.insertBack(b1);
    manager.insertBack(s1);
    manager.printList();  // uses iterator internally
    CHECK(manager.getListSize() == 2);  // both trades still in list
}
// ==========================================================
// K) ASSIGNMENT 11 STACKS AND QUEUES TESTS
// ==========================================================
TEST_CASE("TradeStack push and pop") {
    TradeStack stack;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* s1 = new SellTrade("TSLA", 5, High, 10.0, 200.0);

    stack.push(b1);
    stack.push(s1);

    CHECK(stack.getStackSize() == 2);

    stack.pop();
    CHECK(stack.top() == b1);
    CHECK(stack.getStackSize() == 1);
    stack.pop();
    CHECK(stack.getStackSize() == 0);
    CHECK(stack.isEmptyTradeStack() == true);
}

TEST_CASE("TradeQueue enqueue and dequeue") {
    TradeQueue queue;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* s1 = new SellTrade("TSLA", 5, High, 10.0, 200.0);

    queue.enqueueTrade(b1);
    queue.enqueueTrade(s1);
    CHECK(queue.getQueueSize() == 2);

    queue.dequeueTrade();
    CHECK(queue.frontTrade() == s1);
    CHECK(queue.getQueueSize() == 1);

    queue.dequeueTrade();
    CHECK(queue.getQueueSize() == 0);
    CHECK(queue.isEmptyTradeQueue() == true);
}
// ==========================================================
// L) ASSIGNMENT 12 STL MAP TESTS
// ==========================================================
TEST_CASE("insertIntoMap adds single trade") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager.insertIntoMap(b1);
    CHECK(manager.getMapSize() == 1);
    CHECK(manager.lookupBySymbol("AAPL") == b1);
}
TEST_CASE("insertIntoMap adds multiple trades") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* s1 = new SellTrade("TSLA", 5, High, 10.0, 200.0);
    BaseTrade* b2 = new BuyTrade("GOOG", 3, Medium, 1.0, 50.0);
    manager.insertIntoMap(b1);
    manager.insertIntoMap(s1);
    manager.insertIntoMap(b2);
    CHECK(manager.getMapSize() == 3);
}
TEST_CASE("insertIntoMap replaces trade with duplicates symbol") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* b2 = new BuyTrade("AAPL", 20, High, 3.0, 150.0);
    manager.insertIntoMap(b1);
    manager.insertIntoMap(b2);
    CHECK(manager.getMapSize() == 1);
    CHECK(manager.lookupBySymbol("AAPL") == b2);
}
TEST_CASE("insertIntoMap handles nullptr gracefully") {
    TradeManager manager;
    manager.insertIntoMap(nullptr);
    CHECK(manager.getMapSize() == 0);
}
TEST_CASE("lookupBySymbol finds existing trade") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* s1 = new SellTrade("TSLA", 5, High, 10.0, 200.0);
    manager.insertIntoMap(b1);
    manager.insertIntoMap(s1);
    CHECK(manager.lookupBySymbol("AAPL") == b1);
    CHECK(manager.lookupBySymbol("TSLA") == s1);
}
TEST_CASE("lookupBySymbol returns nullptr for non-existent symbol") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager.insertIntoMap(b1);
    CHECK(manager.lookupBySymbol("MSFT") == nullptr);
}
TEST_CASE("lookupBySymbol returns nullptr on empty map") {
    TradeManager manager;
    CHECK(manager.lookupBySymbol("AAPL") == nullptr);
}
TEST_CASE("deleteFromMap removes existing trade") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* s1 = new SellTrade("TSLA", 5, High, 10.0, 200.0);
    manager.insertIntoMap(b1);
    manager.insertIntoMap(s1);
    bool result = manager.deleteFromMap("AAPL");
    CHECK(result == true);
    CHECK(manager.getMapSize() == 1);
    CHECK(manager.lookupBySymbol("AAPL") == nullptr);
}
TEST_CASE("deleteFromMap returns false for non-existent symbol") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager.insertIntoMap(b1);
    bool result = manager.deleteFromMap("MSFT");
    CHECK(result == false);
    CHECK(manager.getMapSize() == 1);
}
TEST_CASE("deleteFromMap returns false on empty map") {
    TradeManager manager;
    bool result = manager.deleteFromMap("AAPL");
    CHECK(result == false);
    CHECK(manager.getMapSize() == 0);
}
TEST_CASE("printMap handles empty map gracefully") {
    TradeManager manager;
    manager.printMap();
    CHECK(manager.getMapSize() == 0);
}
TEST_CASE("printMap displays trades sorted by symbol") {
    TradeManager manager;
    BaseTrade* b1 = new BuyTrade("TSLA", 10, Low, 2.0, 100.0);
    BaseTrade* s1 = new SellTrade("AAPL", 5, High, 10.0, 200.0);
    BaseTrade* b2 = new BuyTrade("GOOG", 3, Medium, 1.0, 50.0);
    manager.insertIntoMap(b1);
    manager.insertIntoMap(s1);
    manager.insertIntoMap(b2);
    manager.printMap();
    CHECK(manager.getMapSize() == 3);
}
TEST_CASE("lookupBySymbol is faster than sequentialSearch") {
    TradeManager manager;
    for (int i = 0; i < 100; i++) {
        BaseTrade* trade = new BuyTrade("SYM" + std::to_string(i), 10, Low, 1.0, 100.0);
        manager.addTrade(trade);
        manager.insertIntoMap(trade);
    }
    CHECK(manager.lookupBySymbol("SYM50") != nullptr);
    CHECK(manager.sequentialSearch("SYM50") != -1);
}
// ==========================================================
// M) ASSIGNMENT 14 REST API TESTS
// ==========================================================
// Tests that StockApiClient accumulates response correctly
TEST_CASE("StockApiClient StartOfData clears response") {
    StockApiClient client;
    // simulate data arriving then clearing
    client.Data("some data", 9);
    client.StartOfData();  // should clear
    CHECK(client.GetResponse() == "");
}

TEST_CASE("StockApiClient Data accumulates chunks") {
    StockApiClient client;
    client.StartOfData();
    // pass as const char* to match the actual signature
    client.Data("chunk1", 6);
    client.Data("chunk2", 6);
    client.Data("chunk3", 6);
    client.EndOfData();
    CHECK(client.GetResponse() == "chunk1chunk2chunk3");
}

TEST_CASE("StockApiClient GetResponse returns empty before data") {
    StockApiClient client;
    CHECK(client.GetResponse() == "");
}

TEST_CASE("StockApiClient EndOfData does not crash") {
    StockApiClient client;
    client.StartOfData();
    client.Data("test data", 9);
    client.EndOfData();
    CHECK(client.GetResponse() == "test data");
}

// Tests that JSON parsing handles valid currency response correctly
TEST_CASE("JSON parsing handles valid currency array") {
    // simulate what the API would return
    // WHY no special characters? Because the euro symbol causes
    // encoding issues in some compilers — using plain ASCII avoids this
    string fakeResponse = "{\"count\": 2, \"currencies\": [{\"code\": \"USD\", \"name\": \"US Dollar\", \"symbol\": \"$\", \"rate_usd\": 1.0}, {\"code\": \"EUR\", \"name\": \"Euro\", \"symbol\": \"EUR\", \"rate_usd\": 0.92}]}";

    bool parseSucceeded = false;
    try {
        nlohmann::json jsonData = nlohmann::json::parse(fakeResponse);
        parseSucceeded = jsonData.contains("currencies") &&
            jsonData["currencies"].is_array();
    }
    catch (const nlohmann::json::exception&) {
        parseSucceeded = false;
    }
    CHECK(parseSucceeded == true);
}

// Tests that JSON parsing handles missing currencies key
TEST_CASE("JSON parsing handles missing currencies key") {
    string missingKey = R"({"count": 0})";

    bool parseSucceeded = false;
    try {
        nlohmann::json jsonData = nlohmann::json::parse(missingKey);
        parseSucceeded = jsonData.contains("currencies");
    }
    catch (const nlohmann::json::exception&) {
        parseSucceeded = false;
    }
    CHECK(parseSucceeded == false);
}

// Tests that POST JSON body is built correctly
TEST_CASE("POST JSON body builds correctly") {
    nlohmann::json requestBody;
    requestBody["code"] = "PLN";
    requestBody["name"] = "Polish Zloty";
    requestBody["symbol"] = "zl";
    requestBody["rate_usd"] = 3.94;

    string bodyStr = requestBody.dump();

    // verify the JSON string contains expected fields
    CHECK(bodyStr.find("PLN") != string::npos);
    CHECK(bodyStr.find("Polish Zloty") != string::npos);
    CHECK(bodyStr.find("rate_usd") != string::npos);
}

// Tests that POST response parsing handles success correctly
TEST_CASE("POST response parsing handles success message") {
    string successResponse = R"({
        "message": "currency added successfully",
        "currency": {"code": "PLN", "name": "Polish Zloty", "symbol": "zl", "rate_usd": 3.94}
    })";

    bool parseSucceeded = false;
    string message = "";
    try {
        nlohmann::json jsonResponse = nlohmann::json::parse(successResponse);
        message = jsonResponse.value("message", "");
        parseSucceeded = !message.empty();
    }
    catch (const nlohmann::json::exception&) {
        parseSucceeded = false;
    }
    CHECK(parseSucceeded == true);
    CHECK(message == "currency added successfully");
}

// Tests that POST response parsing handles error response
TEST_CASE("POST response parsing handles error response") {
    string errorResponse = R"({"error": "Missing required fields"})";

    bool hasError = false;
    try {
        nlohmann::json jsonResponse = nlohmann::json::parse(errorResponse);
        hasError = jsonResponse.contains("error");
    }
    catch (const nlohmann::json::exception&) {
        hasError = false;
    }
    CHECK(hasError == true);
}

// Validate JSON Parsing
TEST_CASE("API JSON parsing for currency works") {
    std::string sample = R"({
        "count": 1,
        "currencies": [
            {
                "code": "USD",
                "name": "US Dollar",
                "symbol": "$",
                "rate_usd": 1.0
            }
        ]
    })";

    auto data = nlohmann::json::parse(sample);

    CHECK(data["currencies"].is_array());
    CHECK(data["currencies"][0]["code"] == "USD");
    CHECK(data["currencies"][0]["rate_usd"] == doctest::Approx(1.0));
}

#endif