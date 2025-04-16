#include "../header/PFunctionArea.h"

PFunctionArea::PFunctionArea(void) {
}

PFunctionArea::PFunctionArea(int x, int y, int width, int height) :
    menuInitialize(x, y, width, height),
    menuInsert(x, y, width, height) {
    background = {1.f * x, 1.f * y, 1.f * width, 1.f * height};
    state = PSwitchBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + PConstants::PFunctionArea::spaceY}, 
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::outlineBoxColor,
        {"Initialize", "Insert"}, PConstants::PFunctionArea::textSize);
}

PFunctionArea::PFunctionArea(Vector2 pos, Vector2 size) :
    menuInitialize(pos, size),
    menuInsert(pos, size) {
    background = {pos.x, pos.y, size.x, size.y};
    state = PSwitchBox(Vector2{pos.x + PConstants::PFunctionArea::spaceX, pos.y + PConstants::PFunctionArea::spaceY}, 
        Vector2{size.x - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::outlineBoxColor,
        {"Initialize", "Insert"}, PConstants::PFunctionArea::textSize);
};

void PFunctionArea::draw(void) {
    // Draw a background
    DrawRectangleRec(background, PConstants::PFunctionArea::regionColor);

    // Draw state button
    state.draw();

    // Current state: Initialize
    if(currentMode == StateID::Initialize) {
        menuInitialize.draw();
    }
    // Current state: Insert
    else if(currentMode == StateID::Insert) {
        menuInsert.draw();
    }
}

vector<string> PFunctionArea::update(void) {
    // Store request from the user
    vector<string> res;

    // Get current mode
    currentMode = state.update();

    // Current state: Initialize
    if(currentMode == StateID::Initialize) {
        vector<string> ret = menuInitialize.update();
        res.push_back("initialize");
        res.insert(res.end(), ret.begin(), ret.end());
        // Return request: initialize + arguments ...
        return res;
    }
    // Current state: Insert
    else if(currentMode == StateID::Insert) {
        vector<string> ret = menuInsert.update();
        res.push_back("insert");
        res.insert(res.end(), ret.begin(), ret.end());
        // Return request: insert + arguments ...
        return res;
    }

    return vector<string>{"nothing"};
}

void PFunctionArea::prepare(void) {
    menuInitialize.prepare();
}