#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _HAS_STD_BYTE 0
#include "StockApp.h"
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

using namespace std;

#ifndef RUN_TESTS
int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    
    {
        StockApp app;
        app.displayBanner();
        app.showMenu();
    } 

    
    _CrtDumpMemoryLeaks();

    return 0;
}
#endif
