#include "../header/LFunctionArea.h"

LFunctionArea::LFunctionArea() {}

LFunctionArea::LFunctionArea(int x, int y, int width, int height, Color color) {
    background.x = x;
    background.y = y;
    background.width = width;
    background.height = height;
    backgroundColor = color;
    ChooseAction = 1;
}

vector<string> LFunctionArea::draw(void) {
    // Draw a background
    DrawRectangleRec(background, backgroundColor);

    // Current mode: Initialize
    if(ChooseAction == 0) {
        LInitializeMenu menu(background.x, background.y, background.width, background.height, 20);
        menu.draw();
        string ret = menu.draw();
        return vector<string> {"initialize", ret};
    }

    else if(ChooseAction == 1) {
        LInsertMenu menu(background.x, background.y, background.width, background.height, 20);
        string ret = menu.draw();
        return vector<string> {"insert", ret};
    }

    return vector<string>{"nothing"};
}