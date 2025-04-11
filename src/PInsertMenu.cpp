#include "../header/PInsertMenu.h"

PInsertMenu::PInsertMenu(void) {}
PInsertMenu::PInsertMenu(float x, float y, float width, float height) :
    x(x), y(y), width(width), height(height),
    Mode(Vector2{x + PConstants::PFunctionArea::spaceX, y + PConstants::PFunctionArea::boxHeight + 2.f * PConstants::PFunctionArea::spaceY}, Vector2{width - 2.f * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, PConstants::PFunctionArea::boxOutlineThickness, PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::outlineBoxColor, {"Head", "Tail", "After (0-indexed)"}, PConstants::PFunctionArea::textSize),

    GO(
    Vector2{x + PConstants::PFunctionArea::spaceX, y + height - PConstants::PFunctionArea::spaceY - PConstants::PFunctionArea::boxHeight}, 
    Vector2{width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
    PConstants::PFunctionArea::boxOutlineThickness, PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::GOColor, 
    "GO", PConstants::PFunctionArea::textSize
    ),

    headInputBox(Vector2{x + PConstants::PFunctionArea::spaceX, y + 2.f * PConstants::PFunctionArea::boxHeight + 3.f * PConstants::PFunctionArea::spaceY}, Vector2{width - 2.f * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, PConstants::PFunctionArea::boxOutlineThickness, PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::outlineBoxColor, "Value", PConstants::PFunctionArea::textSize),
    tailInputBox(Vector2{x + PConstants::PFunctionArea::spaceX, y + 2.f * PConstants::PFunctionArea::boxHeight + 3.f * PConstants::PFunctionArea::spaceY}, Vector2{width - 2.f * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, PConstants::PFunctionArea::boxOutlineThickness, PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::outlineBoxColor, "Value", PConstants::PFunctionArea::textSize),
    specifiedPositionInputBox(Vector2{x + PConstants::PFunctionArea::spaceX, y + 2.f * PConstants::PFunctionArea::boxHeight + 3.f * PConstants::PFunctionArea::spaceY}, Vector2{PConstants::PFunctionArea::boxHalfWidth, PConstants::PFunctionArea::boxHeight}, PConstants::PFunctionArea::boxOutlineThickness, PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::outlineBoxColor, "Position", PConstants::PFunctionArea::textSize),
    specifiedValueInputBox(Vector2{x + PConstants::PFunctionArea::boxHalfWidth + 2.f * PConstants::PFunctionArea::spaceX, y + 2.f * PConstants::PFunctionArea::boxHeight + 3.f * PConstants::PFunctionArea::spaceY}, Vector2{PConstants::PFunctionArea::boxHalfWidth, PConstants::PFunctionArea::boxHeight}, PConstants::PFunctionArea::boxOutlineThickness, PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::outlineBoxColor, "Value", PConstants::PFunctionArea::textSize) {}
PInsertMenu::PInsertMenu(Vector2 pos, Vector2 size) :
    x(pos.x), y(pos.y), width(size.x), height(size.y),
    Mode(Vector2{x + PConstants::PFunctionArea::spaceX, y + PConstants::PFunctionArea::boxHeight + 2.f * PConstants::PFunctionArea::spaceY}, Vector2{width - 2.f * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, PConstants::PFunctionArea::boxOutlineThickness, PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::outlineBoxColor, {"Head", "Tail", "After (0-indexed)"}, PConstants::PFunctionArea::textSize),

    GO(
    Vector2{x + PConstants::PFunctionArea::spaceX, y + height - PConstants::PFunctionArea::spaceY - PConstants::PFunctionArea::boxHeight}, 
    Vector2{width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
    PConstants::PFunctionArea::boxOutlineThickness, PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::GOColor, 
    "GO", PConstants::PFunctionArea::textSize
    ),

    headInputBox(Vector2{x + PConstants::PFunctionArea::spaceX, y + 2.f * PConstants::PFunctionArea::boxHeight + 3.f * PConstants::PFunctionArea::spaceY}, Vector2{width - 2.f * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, PConstants::PFunctionArea::boxOutlineThickness, PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::outlineBoxColor, "Value", PConstants::PFunctionArea::textSize),
    tailInputBox(Vector2{x + PConstants::PFunctionArea::spaceX, y + 2.f * PConstants::PFunctionArea::boxHeight + 3.f * PConstants::PFunctionArea::spaceY}, Vector2{width - 2.f * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, PConstants::PFunctionArea::boxOutlineThickness, PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::outlineBoxColor, "Value", PConstants::PFunctionArea::textSize),
    specifiedPositionInputBox(Vector2{x + PConstants::PFunctionArea::spaceX, y + 2.f * PConstants::PFunctionArea::boxHeight + 3.f * PConstants::PFunctionArea::spaceY}, Vector2{PConstants::PFunctionArea::boxHalfWidth, PConstants::PFunctionArea::boxHeight}, PConstants::PFunctionArea::boxOutlineThickness, PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::outlineBoxColor, "Position", PConstants::PFunctionArea::textSize),
    specifiedValueInputBox(Vector2{x + PConstants::PFunctionArea::boxHalfWidth + 2.f * PConstants::PFunctionArea::spaceX, y + 2.f * PConstants::PFunctionArea::boxHeight + 3.f * PConstants::PFunctionArea::spaceY}, Vector2{PConstants::PFunctionArea::boxHalfWidth, PConstants::PFunctionArea::boxHeight}, PConstants::PFunctionArea::boxOutlineThickness, PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::outlineBoxColor, "Value", PConstants::PFunctionArea::textSize) {}

void PInsertMenu::draw(void) {
    // Draw and update current mode
    Mode.draw();
    GO.draw();

    // Mode = Head input
    if(currentMode == ModeID::Head) {
        headInputBox.draw();
    }
    // Mode = Tail input
    else if(currentMode == ModeID::Tail) {
        tailInputBox.draw();
    }
    // Mode = Specified position input
    else if(currentMode == ModeID::SpecifiedPosition) {
        specifiedPositionInputBox.draw();
        specifiedValueInputBox.draw();
    }
}

vector<string> PInsertMenu::update(void) {
    currentMode = Mode.update();

    /// I. Update head insert mode
    if(currentMode == ModeID::Head) {
        if(headInputBox.hasContent() && 
            (GO.isClick() || (headInputBox.isChosen && IsKeyPressed(KEY_ENTER)))) {
            return {"head", headInputBox.extract()};
        }
    }
    /// II. Update tail insert mode
    else if(currentMode == ModeID::Tail) {
        if(tailInputBox.hasContent() && 
            (GO.isClick() || (tailInputBox.isChosen && IsKeyPressed(KEY_ENTER)))) {
            return {"tail", tailInputBox.extract()};
        }
    }
    /// III. Update after-a-position insert mode
    else if(currentMode == ModeID::SpecifiedPosition) {
        if(specifiedPositionInputBox.hasContent() && specifiedValueInputBox.hasContent() && (
            GO.isClick() || (
                (specifiedPositionInputBox.isChosen || specifiedValueInputBox.isChosen) && 
                IsKeyPressed(KEY_ENTER)
                )
            )
        ) {
            return {"after", specifiedPositionInputBox.extract(), specifiedValueInputBox.extract()};
        }
    }
    return {"nothing"};
}