#pragma once
#include <raylib.h>
#include "PTitleBox.h"
#include <string>
using namespace std;

struct PInitializeMenu {
    const int boxHeight = 45;
    const int verticalSpace = 5;
    const int horizontalSpace = 5;
    const int boxOutlineThickness = 2;

    int x, y, width, height, characterSize;
    PTitleBox Name, Mode, GO;

    PInitializeMenu(void); // Empty initialize
    PInitializeMenu(int x, int y, int width, int height, int characterSize); // Initialize with size of the background
    string draw(void);
};