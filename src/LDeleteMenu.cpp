#include"../header/LDeleteMenu.h"

LDeleteMenu::LDeleteMenu() {
    
}
LDeleteMenu::LDeleteMenu(int x, int y, int width, int height, int characterSize) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->characterSize = characterSize;
    char goName[] = "GO";
    Mode = PSwitchBox(Vector2{1.f * x + horizontalSpace, 1.f * y + boxHeight + 2 * verticalSpace}, 
                    Vector2{1.f * width - 2 * horizontalSpace, 1.f * boxHeight}, boxOutlineThickness, WHITE, BLACK, {"Delete a node", "Clear"}, characterSize);
    
    GO = PTitleBox(x + horizontalSpace, y + height - horizontalSpace - boxHeight, width - 2 * horizontalSpace, boxHeight, boxOutlineThickness, WHITE, RED, goName, characterSize);
}
string LDeleteMenu::draw(bool active) {
    int chooseAction = Mode.update();
    Mode.draw();
    GO.draw();
    if(GO.isClick() || IsKeyPressed(KEY_ENTER) && active) {
        if(chooseAction == 0) {
            return "delete";
        }
        else if(chooseAction == 1) {
            return "clear";
        }
    }
    return "nothing";
}