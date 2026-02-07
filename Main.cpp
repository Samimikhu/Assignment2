#include "StockApp.h"
#include <iostream>
using namespace std;

// Prevent this main from running if we are doing unit tests
#ifndef RUN_TESTS

int main() {
    
    StockApp app;
    app.displayBanner();
    app.showMenu();
    return 0;
}

#endif
