#include "../header/PInitializeMenu.h"

PInitializeMenu::PInitializeMenu(void) {
}

PInitializeMenu::PInitializeMenu(int x, int y, int width, int height, int characterSize) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->characterSize = characterSize;
    char name[] = "Initialize";
    char modeName[] = "Random";
    char goName[] = "GO";
    Name = PTitleBox(x + horizontalSpace, y + verticalSpace, width - 2 * horizontalSpace, boxHeight, boxOutlineThickness, WHITE, BLACK, name, characterSize);
    Mode = PTitleBox(x + horizontalSpace, y + boxHeight + 2 * verticalSpace, width - 2 * horizontalSpace, boxHeight, boxOutlineThickness, WHITE, BLACK, modeName, characterSize);
    
    GO = PTitleBox(x + horizontalSpace, y + height - horizontalSpace - boxHeight, width - 2 * horizontalSpace, boxHeight, boxOutlineThickness, WHITE, RED, goName, characterSize);
}

string PInitializeMenu::draw(void) {
    Name.draw();
    Mode.draw();
    GO.draw();
    if(GO.isClick()) {
        return "random";
    }
    return "nothing";
}