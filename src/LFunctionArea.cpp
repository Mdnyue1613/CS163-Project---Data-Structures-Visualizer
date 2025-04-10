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

void LFunctionArea::prepare(){
    initializeMenu.prepare();
}

vector<string> LFunctionArea::draw(bool active) {
    vector<string> res;

    // Draw a background
    DrawRectangleRec(background, backgroundColor);

    ChooseAction = Mode.draw();

    // Current mode: Initialize
    if(ChooseAction == 0) {
        vector<string> ret = initializeMenu.draw(active);
        res.push_back("initialize");
        res.insert(res.end(), ret.begin(), ret.end());
        if(active)
            return res;
    }

    else if(ChooseAction == 1) {
        vector<string> ret = insertMenu.draw(active);
        res.push_back("insert");
        res.insert(res.end(), ret.begin(), ret.end());
        if(active) 
            return res;
    }

    else if(ChooseAction == 2) {
        vector<string> ret = deleteMenu.draw(active);
        res.push_back("delete");
        res.insert(res.end(), ret.begin(), ret.end());
        if(active) 
            return res;
    }

    return vector<string>{"nothing"};
}