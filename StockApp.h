/*
Header for StockApp
==========================================================
*/
#pragma once
#include "TradeManager.h"
#include "json.hpp"
#include "HttpClient.h"
#include <string>
using namespace std;

// ===== ASSIGNMENT 14 ADDITION =====
// Derived class from HttpClient
// Overrides StartOfData(), Data(), and EndOfData() to accumulate
// the full HTTP response body into a std::string member variable
// WHY derive from HttpClient? Because the base class handles the
// low level HTTP connection details — we just need to collect
// the response body as it arrives in chunks
class StockApiClient : public HttpClient {
private:
    // ===== ASSIGNMENT 14 ADDITION =====
    // Accumulates the full HTTP response body as it arrives in chunks
    // WHY a string? Because JSON parsing requires the complete response
    // before we can parse it — we cannot parse partial JSON
    string responseBody;

public:
    // ===== ASSIGNMENT 14 ADDITION =====
    // Called once at the start of the response
    // WHY override? To clear any previous response before accumulating new data
    void StartOfData() override {
        responseBody = "";  // clear previous response
    }

    // ===== ASSIGNMENT 14 ADDITION =====
    // Called repeatedly as chunks of response data arrive
    // WHY const char* and size? Because HttpClient passes raw bytes 
    // we append each chunk to build the complete response string
    // WHY override? Because HTTP responses arrive in pieces and we need
    // to collect all of them before we can parse the JSON
    void Data(const char* data, const unsigned int size) override {
        responseBody.append(data, size);  // append raw bytes to build full response
    }

    // ===== ASSIGNMENT 14 ADDITION =====
    // Called once when all response data has been received
    // WHY override? To signal that the response is complete and ready to parse
    void EndOfData() override {
        // response is complete — ready to parse
        // no action needed here but must be overridden
    }

    // ===== ASSIGNMENT 14 ADDITION =====
    // Returns the accumulated response string
    // WHY expose this? So StockApp can retrieve the full response
    // after the HTTP request completes and parse it with nlohmann/json
    string GetResponse() const {
        return responseBody;
    }
};

class StockApp {
private:
    TradeManager manager;
public:
    StockApp();
    void displayBanner();
    void addBuyTrade();
    void addSellTrade();
    void removeTrade();
    void displaySummary();
    // ===== ASSIGNMENT 10 ADDITION =====
    void displayLinkedList();
    // ===== ASSIGNMENT 12 ADDITIONS =====
    void lookupTradeBySymbol();
    void deleteTradeFromMap();
    void displayTradeMap();
    // ===== ASSIGNMENT 14 ADDITIONS =====
    // GET — fetch currencies from API and load into map
    void fetchCurrenciesFromAPI();
    // POST — add a new currency to the API
    void postCurrencyToAPI();
    void showMenu();
};