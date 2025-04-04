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
}
string LInsertMenu::draw(bool active) {
    // Name.draw();
    Mode.draw();
    GO.draw();
    if(GO.isClick() || IsKeyPressed(KEY_ENTER) && active) {
        return "Insert";
    }
    else return "nothing";
}