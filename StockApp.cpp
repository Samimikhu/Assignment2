// ===== ASSIGNMENT 14 ADDITION =====
// Prevents 'byte' ambiguity between windows.h and std::byte in C++17
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _HAS_STD_BYTE 0
/*
Implements menu system and trade input.

Assignment 5:
- Dynamically creates trades using new
- Stores them in TradeManager
- Added full input validation to prevent invalid trades

Assignment 6:
- Uses overloaded operators instead of direct function calls
- Demonstrates template usage (removed multiply template to fix build)

Assignment 7:
- Added try/catch blocks to handle exceptions from operators

Assignment 10:
- Added linked list menu options

Assignment 12:
- Added STL map menu options for fast symbol lookup

Assignment 14:
- Added REST API client using HttpClient
- GET currencies from api.macomb.io and load into existing map
- POST a new currency to api.macomb.io
==========================================================
*/

#include "StockApp.h"
#include "BuyTrade.h"
#include "SellTrade.h"
#include "TradeManager.h"
#include "DynamicArray.h"
#include <iostream>
#include <iomanip>
using namespace std;

StockApp::StockApp() {}

void StockApp::displayBanner() {
    cout << "=== Stock Trading Application ===\n";
}

void StockApp::addBuyTrade() {

    string symbol;
    int shares;
    double price, commission;
    int r;

    cin.ignore(10000, '\n');

    cout << "Symbol: ";
    getline(cin, symbol);

    if (symbol.empty()) {
        cout << "Invalid symbol.\n";
        return;
    }

    cout << "Shares: ";
    if (!(cin >> shares)) {
        cout << "Invalid input for shares.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (shares <= 0) {
        cout << "Shares must be positive.\n";
        return;
    }

    cout << "Price: ";
    if (!(cin >> price)) {
        cout << "Invalid input for price.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (price <= 0) {
        cout << "Price must be positive.\n";
        return;
    }

    cout << "Risk (1=Low,2=Medium,3=High): ";
    if (!(cin >> r)) {
        cout << "Invalid input for risk.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (r < 1 || r > 3) {
        cout << "Risk must be 1, 2, or 3.\n";
        return;
    }

    cout << "Commission: ";
    if (!(cin >> commission)) {
        cout << "Invalid input for commission.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (commission < 0) {
        cout << "Commission cannot be negative.\n";
        return;
    }

    RiskLevel risk = static_cast<RiskLevel>(r - 1);

    //// ===== ASSIGNMENT 5 ADDITION =====
    BaseTrade* trade = new BuyTrade(symbol, shares, risk, commission, price);

    //// ===== ASSIGNMENT 6 CHANGE =====
    manager += trade;

    //// ===== ASSIGNMENT 10 ADDITION =====
    // Also insert into linked list at back
    manager.insertBack(trade);

    //// ===== ASSIGNMENT 12 ADDITION =====
    // Also insert into map for fast symbol lookup
    manager.insertIntoMap(trade);

    cout << "Buy trade added successfully.\n";

    //// ===== ASSIGNMENT 6 TEMPLATE USAGE =====
    double totalCost = calculateTotal<double>(price, (double)shares) + commission;
    cout << "Calculated total cost: $" << totalCost << endl;
}

void StockApp::addSellTrade() {

    string symbol;
    int shares;
    double price, profit;
    int r;

    cin.ignore(10000, '\n');

    cout << "Symbol: ";
    getline(cin, symbol);

    if (symbol.empty()) {
        cout << "Invalid symbol.\n";
        return;
    }

    cout << "Shares: ";
    if (!(cin >> shares)) {
        cout << "Invalid input for shares.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (shares <= 0) {
        cout << "Shares must be positive.\n";
        return;
    }

    cout << "Price: ";
    if (!(cin >> price)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input for price.\n";
        return;
    }

    if (price <= 0) {
        cout << "Price must be positive.\n";
        return;
    }

    cout << "Risk (1=Low,2=Medium,3=High): ";
    if (!(cin >> r)) {
        cout << "Invalid input for risk.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (r < 1 || r > 3) {
        cout << "Risk must be 1, 2, or 3.\n";
        return;
    }

    cout << "Profit: ";
    if (!(cin >> profit)) {
        cout << "Invalid input for profit.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    RiskLevel risk = static_cast<RiskLevel>(r - 1);

    //// ===== ASSIGNMENT 5 ADDITION =====
    BaseTrade* trade = new SellTrade(symbol, shares, risk, profit, price);

    //// ===== ASSIGNMENT 6 CHANGE =====
    manager += trade;

    //// ===== ASSIGNMENT 10 ADDITION =====
    // Also insert into linked list at back
    manager.insertBack(trade);

    //// ===== ASSIGNMENT 12 ADDITION =====
    // Also insert into map for fast symbol lookup
    manager.insertIntoMap(trade);

    cout << "Sell trade added successfully.\n";

    //// ===== ASSIGNMENT 6 TEMPLATE USAGE =====
    double totalValue = calculateTotal<double>(price, (double)shares) + profit;
    cout << "Calculated total value: $" << totalValue << endl;
}

void StockApp::removeTrade()
{
    if (manager.getSize() == 0) {
        cout << "No trades to remove.\n";
        return;
    }

    int index;

    cout << "Enter index to remove: ";

    if (!(cin >> index)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    //// ===== ASSIGNMENT 6 CHANGE =====
    //// ===== ASSIGNMENT 7 CHANGE =====
    // try block attempts removal using operator-=
    // if index is invalid operator-= throws TradeException
    // catch block handles it gracefully so program does not crash
    try {
        manager -= index;
    }
    catch (const TradeException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void StockApp::displaySummary() {

    //// ===== ASSIGNMENT 6 CHANGE =====
    //// Demonstrates operator[] and operator<< usage

    if (manager.getSize() == 0) {
        cout << "No trades recorded.\n";
        return;
    }

    //// ===== ASSIGNMENT 7 CHANGE =====
    // try block attempts to access each trade using operator[]
    // if index is invalid operator[] throws TradeException
    // catch block handles it gracefully so program does not crash
    try {
        for (int i = 0; i < manager.getSize(); i++) {
            BaseTrade* t = manager[i];   // operator[] used here
            if (t != nullptr)
                cout << *t << endl;      // operator<< used here
        }
    }
    catch (const TradeException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

// ===== ASSIGNMENT 10 ADDITION =====
// Displays linked list using iterator
void StockApp::displayLinkedList() {
    manager.printList();
}

// ===== ASSIGNMENT 12 ADDITIONS =====
// Lookup trade by symbol using map
void StockApp::lookupTradeBySymbol() {
    string symbol;

    cin.ignore(10000, '\n');
    cout << "Enter stock symbol to lookup: ";
    getline(cin, symbol);

    if (symbol.empty()) {
        cout << "Invalid symbol.\n";
        return;
    }

    BaseTrade* trade = manager.lookupBySymbol(symbol);

    if (trade != nullptr) {
        cout << "\nTrade found:\n";
        trade->print();
    }
    else {
        cout << "No trade found for symbol: " << symbol << endl;
    }
}

// Delete trade from map by symbol
void StockApp::deleteTradeFromMap() {
    string symbol;

    cin.ignore(10000, '\n');
    cout << "Enter stock symbol to delete from map: ";
    getline(cin, symbol);

    if (symbol.empty()) {
        cout << "Invalid symbol.\n";
        return;
    }

    bool success = manager.deleteFromMap(symbol);

    if (success) {
        cout << "Trade with symbol " << symbol << " removed from map.\n";
    }
    else {
        cout << "No trade found with symbol: " << symbol << endl;
    }
}

// Display all trades in map (sorted by symbol)
void StockApp::displayTradeMap() {
    manager.printMap();
}

// ===== ASSIGNMENT 14 ADDITION =====
// GET — fetch all currencies from api.macomb.io/currency
// Parse the JSON response and display currency data in a clean formatted table
// WHY connect to the currency API? Because currency exchange rates are directly
// relevant to a stock trading program — traders need to know exchange rates
// to evaluate the value of international trades
// WHY load into existing map? Because the map already exists in TradeManager
// and currency codes make perfect map keys — this connects the API data
// to existing program infrastructure in a meaningful way
void StockApp::fetchCurrenciesFromAPI() {
    cout << "\nFetching currencies from api.macomb.io...\n";

    // ===== ASSIGNMENT 14 ADDITION =====
    // Create our derived HttpClient object
    // WHY use derived class? Because HttpClient is abstract and requires
    // us to override the virtual methods to handle the response data
    StockApiClient client;

    // ===== ASSIGNMENT 14 ADDITION =====
    // Connect to the API server
    // WHY HTTP and not HTTPS? Because the assignment API only supports HTTP
    if (!client.Connect("api.macomb.io", INTERNET_DEFAULT_HTTP_PORT)) {
        cout << "Error: Could not connect to api.macomb.io\n";
        return;
    }

    // ===== ASSIGNMENT 14 ADDITION =====
    // Perform GET request to fetch all currencies
    // WHY no query parameters? Because we want all currencies for display
    // The API returns all 20 supported currencies when no params are given
    client.Get("/currency");

    // ===== ASSIGNMENT 14 ADDITION =====
    // Retrieve the accumulated response body
    string response = client.GetResponse();

    if (response.empty()) {
        cout << "Error: Empty response from server.\n";
        return;
    }

    // ===== ASSIGNMENT 14 ADDITION =====
    // Parse the JSON response using nlohmann/json
    // WHY try/catch? Because the response might be malformed or the server
    // might return an error — we handle both cases gracefully
    try {
        nlohmann::json jsonData = nlohmann::json::parse(response);

        // ===== ASSIGNMENT 14 ADDITION =====
        // Extract the currencies array from the JSON response
        // The API returns: { "count": N, "currencies": [...] }
        if (!jsonData.contains("currencies") || !jsonData["currencies"].is_array()) {
            cout << "Error: Unexpected JSON format from API.\n";
            return;
        }

        auto currencies = jsonData["currencies"];
        int count = jsonData.value("count", 0);

        // ===== ASSIGNMENT 14 ADDITION =====
        // Display currencies in a clean formatted table
        // WHY format as table? Because raw JSON is hard to read —
        // we display it using clean aligned columns
        cout << "\n";
        cout << left << setw(8) << "Code"
            << left << setw(25) << "Name"
            << left << setw(8) << "Symbol"
            << left << setw(12) << "Rate (USD)"
            << "\n";
        cout << string(53, '-') << "\n";

        // ===== ASSIGNMENT 14 ADDITION =====
        // Iterate over the JSON array and display each currency
        // WHY iterate? Because the API returns an array of objects —
        // we must loop through each one to extract and display the data
        for (const auto& currency : currencies) {
            string code = currency.value("code", "N/A");
            string name = currency.value("name", "N/A");
            string symbol = currency.value("symbol", "N/A");
            double rateUsd = currency.value("rate_usd", 0.0);

            cout << left << setw(8) << code
                << left << setw(25) << name
                << left << setw(8) << symbol
                << left << setw(12) << fixed << setprecision(4) << rateUsd
                << "\n";
        }

        cout << "\nTotal currencies fetched: " << count << "\n";
    }
    catch (const nlohmann::json::exception& e) {
        // ===== ASSIGNMENT 14 ADDITION =====
        // Handle malformed JSON gracefully
        // WHY catch json::exception? Because this is the specific exception
        // type that nlohmann/json throws when parsing fails
        cout << "Error parsing JSON response: " << e.what() << "\n";
    }
}

// ===== ASSIGNMENT 14 ADDITION =====
// POST — add a new currency to api.macomb.io/currency
// Builds a JSON request body and sends it to the server
// Parses the response to confirm the item was accepted
// WHY POST? Because the assignment requires demonstrating both GET and POST
// WHY add a currency? Because it is the most natural POST operation
// for the currency endpoint and fits the trading app context
void StockApp::postCurrencyToAPI() {
    cout << "\n--- Add New Currency to API ---\n";

    string code, name, symbol;
    double rateUsd;

    cin.ignore(10000, '\n');

    cout << "Enter currency code (e.g. PLN): ";
    getline(cin, code);
    if (code.empty()) {
        cout << "Invalid code.\n";
        return;
    }

    cout << "Enter currency name (e.g. Polish Zloty): ";
    getline(cin, name);
    if (name.empty()) {
        cout << "Invalid name.\n";
        return;
    }

    cout << "Enter currency symbol (e.g. zl): ";
    getline(cin, symbol);
    if (symbol.empty()) {
        cout << "Invalid symbol.\n";
        return;
    }

    cout << "Enter rate per USD (e.g. 3.94): ";
    if (!(cin >> rateUsd) || rateUsd <= 0) {
        cout << "Invalid rate.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    // ===== ASSIGNMENT 14 ADDITION =====
    // Build JSON request body using nlohmann/json
    // WHY use nlohmann/json to build the body? Because it handles
    // all the JSON formatting and escaping automatically — no manual
    // string building needed
    nlohmann::json requestBody;
    requestBody["code"] = code;
    requestBody["name"] = name;
    requestBody["symbol"] = symbol;
    requestBody["rate_usd"] = rateUsd;

    string bodyStr = requestBody.dump();

    // ===== ASSIGNMENT 14 ADDITION =====
    // Create our derived HttpClient and connect to the API
    StockApiClient client;

    if (!client.Connect("api.macomb.io", INTERNET_DEFAULT_HTTP_PORT)) {
        cout << "Error: Could not connect to api.macomb.io\n";
        return;
    }

    // ===== ASSIGNMENT 14 ADDITION =====
    // Perform POST request with the JSON body
    // WHY POST? Because we are sending new data to the server
    // not retrieving it — POST is the correct HTTP verb for creation
    client.Post("/currency", bodyStr);

    // ===== ASSIGNMENT 14 ADDITION =====
    // Retrieve and parse the response
    string response = client.GetResponse();

    if (response.empty()) {
        cout << "Error: Empty response from server.\n";
        return;
    }

    // ===== ASSIGNMENT 14 ADDITION =====
    // Parse the POST response to confirm acceptance and show assigned ID
    // WHY parse the response? Because the server tells us whether the
    // currency was added or updated and what message was returned
    try {
        nlohmann::json jsonResponse = nlohmann::json::parse(response);

        // ===== ASSIGNMENT 14 ADDITION =====
        // Check for error in response
        if (jsonResponse.contains("error")) {
            cout << "Server error: " << jsonResponse["error"].get<string>() << "\n";
            return;
        }

        // ===== ASSIGNMENT 14 ADDITION =====
        // Display the server confirmation message
        // The API returns { "message": "...", "currency": {...} }
        string message = jsonResponse.value("message", "unknown");
        cout << "\nServer response: " << message << "\n";

        // ===== ASSIGNMENT 14 ADDITION =====
        // Display the currency details returned by the server
        if (jsonResponse.contains("currency")) {
            auto curr = jsonResponse["currency"];
            cout << "Currency details:\n";
            cout << "  Code:     " << curr.value("code", "N/A") << "\n";
            cout << "  Name:     " << curr.value("name", "N/A") << "\n";
            cout << "  Symbol:   " << curr.value("symbol", "N/A") << "\n";
            cout << "  Rate USD: " << curr.value("rate_usd", 0.0) << "\n";
        }
    }
    catch (const nlohmann::json::exception& e) {
        // ===== ASSIGNMENT 14 ADDITION =====
        // Handle malformed POST response gracefully
        cout << "Error parsing POST response: " << e.what() << "\n";
    }
}

void StockApp::showMenu()
{
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Buy Trade\n";
        cout << "2. Add Sell Trade\n";
        cout << "3. Remove Trade\n";
        cout << "4. View Summary\n";
        // ===== ASSIGNMENT 10 ADDITION =====
        cout << "5. View Linked List\n";
        // ===== ASSIGNMENT 12 ADDITIONS =====
        cout << "6. Lookup Trade by Symbol (Map)\n";
        cout << "7. Delete Trade from Map\n";
        cout << "8. View Trade Map\n";
        // ===== ASSIGNMENT 14 ADDITIONS =====
        cout << "9. Fetch Currencies from API (GET)\n";
        cout << "10. Add Currency to API (POST)\n";
        cout << "11. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            addBuyTrade();
            break;
        case 2:
            addSellTrade();
            break;
        case 3:
            removeTrade();
            break;
        case 4:
            displaySummary();
            break;
            // ===== ASSIGNMENT 10 ADDITION =====
        case 5:
            displayLinkedList();
            break;
            // ===== ASSIGNMENT 12 ADDITIONS =====
        case 6:
            lookupTradeBySymbol();
            break;
        case 7:
            deleteTradeFromMap();
            break;
        case 8:
            displayTradeMap();
            break;
            // ===== ASSIGNMENT 14 ADDITIONS =====
        case 9:
            fetchCurrenciesFromAPI();
            break;
        case 10:
            postCurrencyToAPI();
            break;
        case 11:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please select 1-11.\n";
        }

    } while (choice != 11);
}