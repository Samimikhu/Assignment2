#include "StockApp.h"
#include <iostream>
using namespace std;

#ifndef RUN_TESTS   // Prevent conflict with unit test main

int main() {
    StockApp app;          
    app.displayBanner();   
    app.showMenu();        
    return 0;
}

#endif
