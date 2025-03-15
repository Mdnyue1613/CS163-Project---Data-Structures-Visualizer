#include "../header/LInputBox.h"

void LTextBox::setTextBox(BOX box) {
    this->box = box;
    this->posNum_x = box.rec.x + 5;
    this->posNum_y = box.rec.y;
    isClick = 0;
}
void LTextBox::setState() {
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, box.rec)) {
                isClick = true; 
            } else {
                isClick = false;
            }
        }
}
void LTextBox::afterMove() {
    Vector2 mouse = GetMousePosition();
    DrawLine(mouse.x, mouse.y, mouse.x, mouse.y + 20, BLACK);
    DrawLine(mouse.x - 4, mouse.y, mouse.x + 4, mouse.y, BLACK);
    DrawLine(mouse.x - 4, mouse.y + 20, mouse.x + 4, mouse.y + 20, BLACK);
}
void LTextBox::afterClick() {
        bool appearLine = fmod(GetTime(), 0.9) < 0.45;
        if (appearLine) {
            DrawLine(posNum_x, posNum_y, posNum_x, posNum_y + box.rec.height, BLACK);
        }
    }
void LTextBox::draw() {
    box.draw();
    if (box.isMove()) {
        HideCursor();
        afterMove();
    } else {
        ShowCursor();
    }
    setState();
    if (isClick) afterClick(); 
}
