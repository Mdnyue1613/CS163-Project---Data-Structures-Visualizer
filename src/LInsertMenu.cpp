#include "../header/LInsertMenu.h"

LInsertMenu::LInsertMenu() {
    
}
LInsertMenu::LInsertMenu(int x, int y, int width, int height, int characterSize) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->characterSize = characterSize;
    char modeName[] = "Input Data";
    char goName[] = "GO";
    Mode = PTitleBox(x + horizontalSpace, y + boxHeight + 2 * verticalSpace, width - 2 * horizontalSpace, boxHeight, boxOutlineThickness, WHITE, BLACK, modeName, characterSize);
    
    GO = PTitleBox(x + horizontalSpace, y + height - horizontalSpace - boxHeight, width - 2 * horizontalSpace, boxHeight, boxOutlineThickness, WHITE, RED, goName, characterSize);
    inputBox = PInputBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + 2 * PConstants::PFunctionArea::boxHeight + 3 * PConstants::PFunctionArea::spaceY},
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight},
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor,
        PConstants::PFunctionArea::outlineBoxColor,
        "input data", PConstants::PFunctionArea::textSize);

}
vector<string> LInsertMenu::draw(bool active) {
    // Name.draw();
    Mode.draw();
    if(active) {
        inputBox.update();
    }
    inputBox.draw();
    GO.draw();
    if((GO.isClick() || IsKeyPressed(KEY_ENTER)) && active && inputBox.hasContent()) {
        return {inputBox.extract()};
    }
    else return {"nothing"};
}