#include "../header/PFunctionArea.h"

PFunctionArea::PFunctionArea(void) {
}

PFunctionArea::PFunctionArea(int x, int y, int width, int height, Color backColor) {
    background.x = x;
    background.y = y;
    background.width = width;
    background.height = height;
    backgroundColor = backColor;
    initialize = true;
}

vector<string> PFunctionArea::draw(void) {
    // Draw a background
    DrawRectangleRec(background, backgroundColor);

    // Current mode: Initialize
    if(initialize) {
        PInitializeMenu menu(background.x, background.y, background.width, background.height, 20);
        string ret = menu.draw();
        return vector<string>{"initialize", ret};
    }

    return vector<string>{"nothing"};
}