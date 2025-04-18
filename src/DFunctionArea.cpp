#include "../header/DFunctionArea.h"

DFunctionArea::DFunctionArea(void) {
}

DFunctionArea::DFunctionArea(int x, int y, int width, int height) :
    menuInitialize(x, y, width, height),
    menuInsert(x, y, width, height),
    menuRemove(x, y, width, height),
    menuSearch(x, y, width, height) {
    background = {1.f * x, 1.f * y, 1.f * width, 1.f * height};
    state = PSwitchBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + PConstants::PFunctionArea::spaceY}, 
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::outlineBoxColor,
        {"Initialize", "Insert", "Remove", "Search"}, PConstants::PFunctionArea::textSize);
}

DFunctionArea::DFunctionArea(Vector2 pos, Vector2 size) :
    menuInitialize(pos, size),
    menuInsert(pos, size),
    menuRemove(pos, size),
    menuSearch(pos, size) {
    background = {pos.x, pos.y, size.x, size.y};
    state = PSwitchBox(Vector2{pos.x + PConstants::PFunctionArea::spaceX, pos.y + PConstants::PFunctionArea::spaceY}, 
        Vector2{size.x - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::outlineBoxColor,
        {"Initialize", "Insert", "Remove", "Search"}, PConstants::PFunctionArea::textSize);
};

void DFunctionArea::draw(void) {
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
    // Current state: Remove
    else if(currentMode == StateID::Remove) {
        menuRemove.draw();
    }
    // Current state: Search
    else if(currentMode == StateID::Search) {
        menuSearch.draw();
    }
}

vector<string> DFunctionArea::update(void) {
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
    // Current state: Remove
    else if(currentMode == StateID::Remove) {
        vector<string> ret = menuRemove.update();
        res.push_back("remove");
        res.insert(res.end(), ret.begin(), ret.end());

        return res;
    }
    // Current state: Search
    else if(currentMode == StateID::Search) {
        vector<string> ret = menuSearch.update();
        res.push_back("search");
        res.insert(res.end(), ret.begin(), ret.end());
        // Return request: search + arguments ...
        return res;
    }

    return vector<string>{"nothing"};
}

void DFunctionArea::prepare(void) {
    menuInitialize.prepare();
}