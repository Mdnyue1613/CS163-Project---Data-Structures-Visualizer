#include "../header/PFunctionArea.h"

PFunctionArea::PFunctionArea(void) {
}

PFunctionArea::PFunctionArea(int x, int y, int width, int height, Color backColor) :
    menuInitialize(x, y, width, height, Constants::functionArea::textSize) {
    background.x = x;
    background.y = y;
    background.width = width;
    background.height = height;
    backgroundColor = backColor;
    initialize = true;
}

PFunctionArea::PFunctionArea(Vector2 pos, Vector2 size, Color backColor) :
    menuInitialize(pos, size, Constants::functionArea::textSize) {
    background = {pos.x, pos.y, size.x, size.y};
    backgroundColor = backColor;
    initialize = true;
};

vector<string> PFunctionArea::draw(void) {
    // Draw a background
    DrawRectangleRec(background, backgroundColor);
    vector<string> res;

    // Current mode: Initialize
    if(initialize) {
        vector<string> ret = menuInitialize.draw();
        res.push_back("initialize");
        res.insert(res.end(), ret.begin(), ret.end());
        return res;
    }

    return vector<string>{"nothing"};
}