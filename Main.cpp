#include "StockApp.h"
using namespace std;
#ifndef RUN_TESTS

int main() {
    StockApp app;
    app.displayBanner();
    app.showMenu();
    return 0;
}

#endif