#include "../header/PFunctionArea.h"

PFunctionArea::PFunctionArea(void) {
}

PFunctionArea::PFunctionArea(int x, int y, int width, int height) :
    menuInitialize(x, y, width, height) {
    background = {1.f * x, 1.f * y, 1.f * width, 1.f * height};
    initialize = true;
    state = PSwitchBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + PConstants::PFunctionArea::spaceY}, 
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::outlineBoxColor,
        {"Initialize", "Insert"}, PConstants::PFunctionArea::textSize);
}

PFunctionArea::PFunctionArea(Vector2 pos, Vector2 size) :
    menuInitialize(pos, size) {
    background = {pos.x, pos.y, size.x, size.y};
    initialize = true;
    state = PSwitchBox(Vector2{pos.x + PConstants::PFunctionArea::spaceX, pos.y + PConstants::PFunctionArea::spaceY}, 
        Vector2{size.x - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::outlineBoxColor,
        {"Initialize", "Insert"}, PConstants::PFunctionArea::textSize);
};

vector<string> PFunctionArea::draw(void) {
    // Store request from the user
    vector<string> res;

    // Draw a background
    DrawRectangleRec(background, PConstants::PFunctionArea::regionColor);

    // Draw state button
    int currentMode = state.draw();

    // Current state: Initialize
    if(currentMode == StateID::Initialize) {
        menuInitialize.draw();
        vector<string> ret = menuInitialize.update();
        res.push_back("initialize");
        res.insert(res.end(), ret.begin(), ret.end());
        // Return request: initialize + arguments ...
        return res;
    }
    // Current state: Insert
    else if(currentMode == StateID::Insert) {

    }

    return vector<string>{"nothing"};
}

void PFunctionArea::prepare(void) {
    menuInitialize.prepare();
}