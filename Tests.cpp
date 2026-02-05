#ifdef RUN_TESTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "BuyTrade.h"
#include "SellTrade.h"
#include "TradeCost.h"

// ---------------- A) CONSTRUCTORS ----------------

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

// ---------------- B) GETTERS AND SETTERS ----------------

TEST_CASE("BuyTrade getters and setters work") {
    BuyTrade b;
    b.setName("MSFT");
    b.setShares(8);
    b.setRisk(Low);
    b.setCommission(3.0);
    b.setPrice(150.0);

    CHECK(b.getName() == "MSFT");
    CHECK(b.getShares() == 8);
    CHECK(b.getRisk() == Low);
    CHECK(b.getCommission() == 3.0);
    CHECK(b.getPrice() == 150.0);
}

TEST_CASE("SellTrade getters and setters work") {
    SellTrade s;
    s.setName("TSLA");
    s.setShares(2);
    s.setRisk(Medium);
    s.setProfit(20.0);
    s.setPrice(300.0);

    CHECK(s.getName() == "TSLA");
    CHECK(s.getShares() == 2);
    CHECK(s.getRisk() == Medium);
    CHECK(s.getProfit() == 20.0);
    CHECK(s.getPrice() == 300.0);
}

// ---------------- C) COMPOSITION CLASS ----------------

TEST_CASE("TradeCost calculates total value") {
    TradeCost cost(50.0);
    CHECK(cost.getPrice() == 50.0);
    CHECK(cost.totalValue(4) == doctest::Approx(200.0));
}

// ---------------- D) DERIVED CLASS CALCULATION ----------------

TEST_CASE("BuyTrade total cost calculation") {
    BuyTrade b("FB", 10, Low, 2.0, 100.0);
    double total = b.getPrice() * b.getShares() + b.getCommission();
    CHECK(total == doctest::Approx(1002.0));
}

TEST_CASE("SellTrade total value calculation") {
    SellTrade s("NFLX", 5, High, 10.0, 200.0);
    double total = s.getPrice() * s.getShares() + s.getProfit();
    CHECK(total == doctest::Approx(1010.0));
}

#endif
