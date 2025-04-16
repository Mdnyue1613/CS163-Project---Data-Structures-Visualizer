#include "../header/PSearchMenu.h"

PSearchMenu::PSearchMenu(void) {}

PSearchMenu::PSearchMenu(float x, float y, float width, float height) :
    x(x), y(y), width(width), height(height), 
    InputBox({x + PConstants::PFunctionArea::spaceX, y + PConstants::PFunctionArea::boxHeight + 2.f * PConstants::PFunctionArea::spaceY}, 
        {width - 2.f * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness,
        PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::outlineBoxColor, 
        "Input a position", PConstants::PExplanationArea::fontSize),
    GO({x + PConstants::PFunctionArea::spaceX, y + height - PConstants::PFunctionArea::spaceY - PConstants::PFunctionArea::boxHeight}, 
        {width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::GOColor, 
        "GO", PConstants::PFunctionArea::textSize) {}

PSearchMenu::PSearchMenu(Vector2 pos, Vector2 size) :
    x(pos.x), y(pos.y), width(size.x), height(size.y),
    InputBox({x + PConstants::PFunctionArea::spaceX, y + PConstants::PFunctionArea::boxHeight + 2.f * PConstants::PFunctionArea::spaceY}, 
        {width - 2.f * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness,
        PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::outlineBoxColor, 
        "Input a value", PConstants::PExplanationArea::fontSize),
    GO({x + PConstants::PFunctionArea::spaceX, y + height - PConstants::PFunctionArea::spaceY - PConstants::PFunctionArea::boxHeight}, 
        {width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, PConstants::PFunctionArea::GOColor, 
        "GO", PConstants::PFunctionArea::textSize) {}

void PSearchMenu::draw(void) {
    InputBox.draw();
    GO.draw();
}

vector<string> PSearchMenu::update(void) {
    vector<string> res;

    if(InputBox.hasContent() && (GO.isClick() || (InputBox.isChosen && IsKeyPressed(KEY_ENTER)))) {
        res.push_back(InputBox.extract());
        return res;
    }
    InputBox.update();

    return {"nothing"};
}