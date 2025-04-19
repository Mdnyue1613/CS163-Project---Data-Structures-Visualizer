#include "../header/DInsertMenu.h"


DInsertMenu::DInsertMenu(void) {}

DInsertMenu::~DInsertMenu(void) {}

DInsertMenu::DInsertMenu(int x, int y, int width, int height) :
    x(x), y(y), width(width), height(height) {
    Mode = PSwitchBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + PConstants::PFunctionArea::boxHeight + 2 * PConstants::PFunctionArea::spaceY}, 
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::outlineBoxColor, 
        {"Single", "List"}, PConstants::PFunctionArea::textSize);
    InputBox = PInputBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + 2 * PConstants::PFunctionArea::boxHeight + 3 * PConstants::PFunctionArea::spaceY},
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight},
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor,
        PConstants::PFunctionArea::outlineBoxColor,
        "Value", PConstants::PFunctionArea::textSize);
    InputFileBox = PIconBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + 3 * PConstants::PFunctionArea::boxHeight + 4 * PConstants::PFunctionArea::spaceY},
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight},
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::iconBoxColor,
        PConstants::PFunctionArea::outlineBoxColor,
        "Assets/Images/PFileIcon.png");
    GO = PTitleBox(Vector2{x + PConstants::PFunctionArea::spaceX, y + height - PConstants::PFunctionArea::spaceY - PConstants::PFunctionArea::boxHeight}, 
        Vector2{width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::GOColor, 
        "GO", 
        PConstants::PFunctionArea::textSize);
}

DInsertMenu::DInsertMenu(Vector2 pos, Vector2 size) :
    x(pos.x), y(pos.y), width(size.x), height(size.y) {
    Mode = PSwitchBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + PConstants::PFunctionArea::boxHeight + 2 * PConstants::PFunctionArea::spaceY}, 
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::outlineBoxColor, 
        {"Single", "List"}, PConstants::PFunctionArea::textSize);
    InputBox = PInputBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + 2 * PConstants::PFunctionArea::boxHeight + 3 * PConstants::PFunctionArea::spaceY},
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight},
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor,
        PConstants::PFunctionArea::outlineBoxColor,
        "Value", PConstants::PFunctionArea::textSize);
    InputFileBox = PIconBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + 3 * PConstants::PFunctionArea::boxHeight + 4 * PConstants::PFunctionArea::spaceY},
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight},
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::iconBoxColor,
        PConstants::PFunctionArea::outlineBoxColor,
        "Assets/Images/PFileIcon.png");
    GO = PTitleBox(Vector2{x + PConstants::PFunctionArea::spaceX, y + height - PConstants::PFunctionArea::spaceY - PConstants::PFunctionArea::boxHeight}, 
        Vector2{width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::GOColor, 
        "GO", 
        PConstants::PFunctionArea::textSize);
}

void DInsertMenu::draw(void) {
    // Draw mode button
    Mode.draw();

    // Draw GO button
    GO.draw();

    // Mode = Head input
    if(currentMode == ModeID::Single) {
        InputBox.draw();
    }
    // Mode = Tail input
    else if(currentMode == ModeID::List) {
        InputBox.draw();
        InputFileBox.draw();
    }

}

vector<string> DInsertMenu::update(void) {
    currentMode = Mode.update();

    /// I. Update head insert mode
    if(currentMode == ModeID::Single) {
        if(InputBox.hasContent() && 
            (GO.isClick() || (InputBox.isChosen && IsKeyPressed(KEY_ENTER)))) {
            return {"single", InputBox.extract()};
        }
        // Update headInputBox for rendering
        InputBox.update();
    }
    /// II. Update tail insert mode
    else if(currentMode == ModeID::List) {
        if(InputBox.hasContent() && 
            (GO.isClick() || (InputBox.isChosen && IsKeyPressed(KEY_ENTER)))) {
            return {"list", InputBox.extract()};
        }
        // Update tailInputBox for rendering
        InputBox.update();
    }
    return {"nothing"};
}