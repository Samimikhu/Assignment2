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
#include "DynamicArray.h" // new
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
// F) ASSIGNMENT 6 ADDITIONS
// ==========================================================

// Operator== test
TEST_CASE("BuyTrade equality") {
    BuyTrade b1("AAPL", 10, Medium, 5.0, 100.0);
    BuyTrade b2("AAPL", 10, Low, 2.0, 50.0);
    BuyTrade b3("MSFT", 10, Medium, 5.0, 100.0);
    CHECK(b1 == b2);
    CHECK_FALSE(b1 == b3);
}

// Operator<< test
TEST_CASE("Operator<<") {
    BuyTrade b("AAPL", 10, Medium, 5.0, 100.0);
    std::ostringstream out;
    out << b;
    CHECK(out.str().find("[BUY]") != std::string::npos);
}

// TradeManager operator[] test
TEST_CASE("TradeManager indexing") {
    TradeManager manager;
    BaseTrade* b = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager.addTrade(b);
    CHECK(manager[0] == b);
    CHECK(manager[-1] == nullptr); // out-of-bounds
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
// G) FUNCTION TEMPLATE TEST
// ==========================================================

TEST_CASE("Function template multiply works with int") {
    int result = multiply(5, 4); // from StockApp.cpp
    CHECK(result == 20);
}

TEST_CASE("Function template multiply works with double") {
    double result = multiply(2.5, 4.0);
    CHECK(result == doctest::Approx(10.0));
}

// ==========================================================
// H) CLASS TEMPLATE TEST
// ==========================================================

TEST_CASE("DynamicArray template add/remove") {
    DynamicArray<int> arr;
    arr.add(10);
    arr.add(20);
    CHECK(arr.getSize() == 2);
    CHECK(arr[0] == 10);
    CHECK(arr[1] == 20);

    arr.remove(0);
    CHECK(arr.getSize() == 1);
    CHECK(arr[0] == 20);
}

TEST_CASE("DynamicArray template bounds checking") {
    DynamicArray<int> arr;
    arr.add(42);
    CHECK(arr[0] == 42);
    CHECK(arr[-1] == 0); // dummy value
    CHECK(arr[100] == 0); // dummy value
}

#endif
