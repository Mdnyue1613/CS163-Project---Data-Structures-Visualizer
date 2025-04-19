#include "../header/PFunctionArea.h"
#include "../header/PConstants.h"

PFunctionArea::PFunctionArea(void) {
}

PFunctionArea::PFunctionArea(int x, int y, int width, int height) :
    menuInitialize(x, y, width, height),
    menuInsert(x, y, width, height),
    menuRemove(x, y, width, height),
    menuSearch(x, y, width, height),
    menuUpdate(x,y , width, height) {
    background = {1.f * x, 1.f * y, 1.f * width, 1.f * height};
    state = PSwitchBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + PConstants::PFunctionArea::spaceY}, 
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::outlineBoxColor,
        {"Initialize", "Insert", "Remove", "Search", "Update"}, PConstants::PFunctionArea::textSize);
}

PFunctionArea::PFunctionArea(Vector2 pos, Vector2 size) :
    menuInitialize(pos, size),
    menuInsert(pos, size),
    menuRemove(pos, size),
    menuSearch(pos, size),
    menuUpdate(pos, size) {
    background = {pos.x, pos.y, size.x, size.y};
    state = PSwitchBox(Vector2{pos.x + PConstants::PFunctionArea::spaceX, pos.y + PConstants::PFunctionArea::spaceY}, 
        Vector2{size.x - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::outlineBoxColor,
        {"Initialize", "Insert", "Remove", "Search", "Update"}, PConstants::PFunctionArea::textSize);
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
    // Remove
    else if(currentMode == Remove) {
        menuRemove.draw();
    }
    // Search
    else if(currentMode == Search) {
        menuSearch.draw();
    }
    // Update
    else if(currentMode == Update) {
        menuUpdate.draw();
    }
}

vector<string> PFunctionArea::update(void) {
    // Result
    vector<string> res;

    // Get current mode
    currentMode = state.update();

    // Current state: Initialize
    if(currentMode == Initialize) {
        vector<string> ret = menuInitialize.update();
        res.push_back("initialize");
        res.insert(res.end(), ret.begin(), ret.end());
        // Return request: initialize + arguments ...
        return res;
    }
    // Current state: Insert
    else if(currentMode == Insert) {
        vector<string> ret = menuInsert.update();
        res.push_back("insert");
        res.insert(res.end(), ret.begin(), ret.end());
        // Return request: insert + arguments ...
        return res;
    }
    // Current state: Remove
    else if(currentMode == Remove) {
        vector<string> ret = menuRemove.update();
        res.push_back("remove");
        // remove + arguments
        res.insert(res.end(), ret.begin(), ret.end());
        return res;
    }
    // Current state: Search
    else if(currentMode == Search) {
        vector<string> ret = menuSearch.update();
        res.push_back("search");
        // search + arguments
        res.insert(res.end(), ret.begin(), ret.end());
        return res;
    }
    // Update
    else if(currentMode == Update) {
        vector<string> ret = menuUpdate.update();
        res.push_back("update");
        // update + arguments
        res.insert(res.end(), ret.begin(), ret.end());
        return res;
    }
    // No request
    return {"nothing"};
}

void PFunctionArea::prepare(void) {
    menuInitialize.prepare();
}