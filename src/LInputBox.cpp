#include "../header/LInputBox.h"

LInputBox::LInputBox() {
    Rectangle a = {6, 200, 293.9, 44.6};
    BOX box;
    box.setRec(a);
    box.setColor(WHITE);
    box.setOutline(BLACK);
    setInputBox(box);
    data = 0;
    inputData = "";
    fontText = 25;
}
void LInputBox::setInputBox(BOX box) {
    this->box = box;
    this->posNum_x = box.rec.x + 5;
    this->posNum_y = box.rec.y;
    isClick = 0;
}
void LInputBox::setState() {
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, box.rec)) {
                isClick = true; 
            } else {
                isClick = false;
            }
        }
}
void LInputBox::afterMove() {
    Vector2 mouse = GetMousePosition();
    DrawLine(mouse.x, mouse.y, mouse.x, mouse.y + 20, BLACK);
    DrawLine(mouse.x - 4, mouse.y, mouse.x + 4, mouse.y, BLACK);
    DrawLine(mouse.x - 4, mouse.y + 20, mouse.x + 4, mouse.y + 20, BLACK);
}
void LInputBox::afterClick(bool appearLine) {
        int key = GetCharPressed();
        while(key > 0) {
            if(key >= '0' && key <= '9' && inputData.size() < 9) {
                inputData += (char) key;
            }
            key = GetCharPressed();
        }
        
        int keyPress = GetKeyPressed();
        while (keyPress > 0) {
            if(IsKeyPressed(KEY_BACKSPACE) && inputData.size() > 0) inputData.pop_back();
            keyPress = GetKeyPressed();
        }
        posNum_x = posText_x + (inputData.size() == 0 ? 0 : MeasureText(inputData.c_str(), fontText));
        if(inputData.size()) data = stoi(inputData);
        if (appearLine) {
            DrawLine(posNum_x, posNum_y , posNum_x, posNum_y + box.rec.height, BLACK);
        }
    }
void LInputBox::draw(bool active) {
    box.draw();
    if(active) {
        if (box.isMove()) {
            HideCursor();
            afterMove();
        } else {
            ShowCursor();
        }
        setState();
        bool appearLine = fmod(GetTime(), 0.8) < 0.4;
        if (isClick) afterClick(appearLine);
        if (inputData.size() > 0) DrawText(inputData.c_str(), posText_x, posText_y, fontText, BLACK);
    }
    else {
        ShowCursor();
    }
}