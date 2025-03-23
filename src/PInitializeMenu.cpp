#include "../header/PInitializeMenu.h"

PInitializeMenu::PInitializeMenu(void) {
}

PInitializeMenu::PInitializeMenu(int x, int y, int width, int height) :
    x(x), y(y), width(width), height(height) {
    Mode = PSwitchBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + PConstants::PFunctionArea::boxHeight + 2 * PConstants::PFunctionArea::spaceY}, 
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::outlineBoxColor, 
        {"Random", "Input"}, PConstants::PFunctionArea::textSize);
    GO = PTitleBox(Vector2{x + PConstants::PFunctionArea::spaceX, y + height - PConstants::PFunctionArea::spaceY - PConstants::PFunctionArea::boxHeight}, 
        Vector2{width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::GOColor, 
        "GO", 
        PConstants::PFunctionArea::textSize);
}

PInitializeMenu::PInitializeMenu(Vector2 pos, Vector2 size) :
    x(pos.x), y(pos.y), width(size.x), height(size.y) {
    Mode = PSwitchBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + PConstants::PFunctionArea::boxHeight + 2 * PConstants::PFunctionArea::spaceY}, 
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::outlineBoxColor, 
        {"Random", "Input"}, PConstants::PFunctionArea::textSize);
    GO = PTitleBox(Vector2{x + PConstants::PFunctionArea::spaceX, y + height - PConstants::PFunctionArea::spaceY - PConstants::PFunctionArea::boxHeight}, 
        Vector2{width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::GOColor, 
        "GO", 
        PConstants::PFunctionArea::textSize);
}

vector<string> PInitializeMenu::draw(void) {
    int currentMode = Mode.draw();
    GO.draw();
    
    if(currentMode == ModeID::Random) {
        if(GO.isClick())
            return {"random"};
    }
    else if(currentMode == ModeID::Input) {

    }
    return {"nothing"};
}