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
    inputBox = PInputBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + 2 * PConstants::PFunctionArea::boxHeight + 3 * PConstants::PFunctionArea::spaceY},
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight},
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor,
        PConstants::PFunctionArea::outlineBoxColor,
        "Number of nodes", PConstants::PFunctionArea::textSize);
    inputFile = PIconBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + 3 * PConstants::PFunctionArea::boxHeight + 4 * PConstants::PFunctionArea::spaceY},
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight},
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::iconBoxColor,
        PConstants::PFunctionArea::outlineBoxColor,
        "Assets/Images/PFileIcon.png");
    
}

void LInitializeMenu::prepare() {
    inputFile.prepare();
}

vector<string> LInitializeMenu::draw(bool active) {
    // Draw
    int chooseAction = Mode.draw();
    if(chooseAction == 0) {
        inputBox.changeTitle("Number of nodes");
        inputBox.draw();
    }
    else if(chooseAction == 1) {
        inputBox.changeTitle("Input a list");
        inputBox.draw();
        inputFile.draw();
    }
    GO.draw();

    // Update
    if(chooseAction == 0) {
        if(active) {
            inputBox.update();
        }
        if(GO.isClick() || IsKeyPressed(KEY_ENTER) && active) {
            vector<string> ret;
            ret.push_back("random");
            if(inputBox.hasContent())
                ret.push_back(inputBox.extract());
            return ret;
        }
    }
    else if(chooseAction == 1) {
        if(active) {
            inputBox.update();
        }
        if((GO.isClick() || IsKeyPressed(KEY_ENTER)) && active && inputBox.hasContent()) {
            return {"data", inputBox.extract()};
        }
    }
    
    return {"nothing"};
}