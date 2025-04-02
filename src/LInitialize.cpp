#include"../header/LInitialize.h"


LInitializeMenu::LInitializeMenu() {
    
}
LInitializeMenu::LInitializeMenu(int x, int y, int width, int height, int characterSize) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->characterSize = characterSize;
    char modeName[] = "Random";
    char goName[] = "GO";
    Mode = PSwitchBox(Vector2{1.f * x + horizontalSpace, 1.f * y + boxHeight + 2 * verticalSpace}, 
                    Vector2{1.f * width - 2 * horizontalSpace, 1.f * boxHeight}, boxOutlineThickness, WHITE, BLACK, {"Random", "Input"}, characterSize);
    
    GO = PTitleBox(x + horizontalSpace, y + height - horizontalSpace - boxHeight, width - 2 * horizontalSpace, boxHeight, boxOutlineThickness, WHITE, RED, goName, characterSize);
}
string LInitializeMenu::draw() {
    int chooseAction = Mode.draw();
    GO.draw();
    if(GO.isClick()) {
        return "random";
    }
    else return "nothing";
}