#include <stdio.h>

#include "ui/UI.h"
#include "data/DataManager.h"

int main() {
    system("color 70");
    DataManager_init();
    DataManager_load(LITERAL("data"));
    UI_mainLoop();
    DataManager_finalize();
    return 0;
}