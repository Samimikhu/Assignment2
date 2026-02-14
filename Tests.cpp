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
#include <sstream>

// ==========================================================
// A) CONSTRUCTOR TESTSSS
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

//// ===== ASSIGNMENT 5 FEATURE TEST =====
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

//// ===== ASSIGNMENT 5 FEATURE TEST =====
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

//// ===== ASSIGNMENT 5 FEATURE TEST =====
TEST_CASE("TradeManager calls print() through base class pointers") {

    TradeManager manager;

    BaseTrade* b1 = new BuyTrade("AAPL", 10, Low, 2.0, 100.0);
    BaseTrade* s1 = new SellTrade("TSLA", 5, High, 10.0, 200.0);

    manager.addTrade(b1);
    manager.addTrade(s1);

    // Call print through base pointers
    manager.printAll();

    // If program reaches here, virtual calls worked
    CHECK(manager.getSize() == 2);
}

#endif
