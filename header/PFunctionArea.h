#pragma once
#include <raylib.h>

struct PFunctionArea {
    Rectangle background;
    Color backgroundColor;
    
    PFunctionArea(void); // initialize
    PFunctionArea(int x, int y, int width, int height, Color backColor); // initialize with parameters
    void draw(void); // draw
};