#include "../header/LFunctionArea.h"

LFunctionArea::LFunctionArea() {}

LFunctionArea::LFunctionArea(int x, int y, int width, int height, Color color) :
    initializeMenu(x, y, width, height, 20),
    insertMenu(x, y, width, height, 20),
    deleteMenu(x, y, width, height, 20) {
    background.x = x;
    background.y = y;
    background.width = width;
    background.height = height;
    backgroundColor = color;
    ChooseAction = 1;
    Mode = PSwitchBox(Vector2{1.f * x + horizontalSpace, 1.f * y + verticalSpace}, Vector2{1.f * width - 2 * horizontalSpace, 1.f * boxHeight}, boxOutlineThickness, WHITE, BLACK, {"Initialize", "Insert", "Delete", "Find"}, 20);
}

vector<string> LFunctionArea::draw(bool active) {
    // Draw a background
    DrawRectangleRec(background, backgroundColor);

    ChooseAction = Mode.update();
    Mode.draw();

    // Current mode: Initialize
    if(ChooseAction == 0) {
        string ret = initializeMenu.draw(active);
        if(active) 
            return vector<string> {"initialize", ret};
    }

    else if(ChooseAction == 1) {
        string ret = insertMenu.draw(active);
        if(active) 
            return vector<string> {"insert", ret};
    }

    else if(ChooseAction == 2) {
        string ret = deleteMenu.draw(active);
        if(active) 
            return vector<string> {"delete", ret};
    }

    return vector<string>{"nothing"};
}