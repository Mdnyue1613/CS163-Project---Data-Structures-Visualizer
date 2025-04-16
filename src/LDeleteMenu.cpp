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
    inputBox = PInputBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + 2 * PConstants::PFunctionArea::boxHeight + 3 * PConstants::PFunctionArea::spaceY},
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight},
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor,
        PConstants::PFunctionArea::outlineBoxColor,
        "input data", PConstants::PFunctionArea::textSize);
}
vector<string> LDeleteMenu::draw(bool active) {
    int chooseAction = Mode.update();
    Mode.draw();
    if(active) {
        inputBox.update();
    }
    inputBox.draw();
    GO.draw();
    if((GO.isClick() || IsKeyPressed(KEY_ENTER)) && active) {
        if(chooseAction == 0) {
            if(inputBox.hasContent()) return {"delete", inputBox.extract()};
            else return {"delete", ""};
        }
        else if(chooseAction == 1) {
            return {"clear"};
        }
    }
    return {"nothing"};
}