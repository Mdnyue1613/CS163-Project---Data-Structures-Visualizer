#include "../header/InputBox.h"

void TextBox::setTextBox(BOX box) {
    this->box = box;
    this->posNum_x = box.rec.x + 10;
    this->posNum_y = box.rec.y;
    isClick = 0;
}
void TextBox::setState() {
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, box.rec)) {
                isClick = true; 
            } else {
                isClick = false;
            }
        }
}
void TextBox::afterMove() {
    Vector2 mouse = GetMousePosition();
    DrawLine(mouse.x, mouse.y, mouse.x, mouse.y + 20, BLACK);
    DrawLine(mouse.x - 4, mouse.y, mouse.x + 4, mouse.y, BLACK);
    DrawLine(mouse.x - 4, mouse.y + 20, mouse.x + 4, mouse.y + 20, BLACK);
}
void TextBox::afterClick() {
        bool appearLine = fmod(GetTime(), 1.0) < 0.5;
        if (appearLine) {
            DrawLine(posNum_x, posNum_y, posNum_x, posNum_y + box.rec.height, BLACK);
        }
    }
void TextBox::draw() {
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
