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
TEST_CASE("TradeManager indexing") {
    TradeManager manager;
    BaseTrade* b = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    manager.addTrade(b);
    CHECK(manager[0] == b);
    CHECK(manager[-1] == nullptr);
    CHECK(manager[99] == nullptr);
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
// Class template tests
TEST_CASE("DynamicArray resizes and stores correctly") {
    DynamicArray<int> arr(2);  // capacity of 2
    arr.add(1);
    arr.add(2);
    arr.add(3);  // triggers resize — capacity doubles to 4
    arr.add(4);
    CHECK(arr.getSize() == 4);  // all 4 items stored after resize
    CHECK(arr[0] == 1);         // items preserved after resize
    CHECK(arr[3] == 4);
}
TEST_CASE("DynamicArray removes and shifts correctly") {
    DynamicArray<int> arr(4);
    arr.add(10);
    arr.add(20);
    arr.add(30);
    arr.remove(1);              // remove middle item (20)
    CHECK(arr.getSize() == 2);  // size decreased
    CHECK(arr[0] == 10);        // first item unchanged
    CHECK(arr[1] == 30);        // shifted left correctly
}

#endif