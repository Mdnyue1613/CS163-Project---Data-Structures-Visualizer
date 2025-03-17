#include "../header/LInputBox.h"

LTextBox::LTextBox() {
    Rectangle a = {6, 200, 293.9, 44.6};
    BOX box;
    box.setRec(a);
    box.setColor(WHITE);
    box.setOutline(BLACK);
    setTextBox(box);
}
void LTextBox::setTextBox(BOX box) {
    this->box = box;
    this->posNum_x = box.rec.x + 5;
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

void LOptionBox::setOption(char option[]) {
    strcpy(this->option, option);
}
void LOptionBox::setBox(BOX box) {
    this->box = box;
}

void LOptionBox::draw() {
    box.draw();
    if (box.isMove()) {
        box.setColor(GRAY);
    }
    else {
        box.setColor(WHITE);
    }
    float textWidth = MeasureText(option, 16);
    float text_x = box.rec.x + box.rec.width / 2 - textWidth / 2;
    float text_y = box.rec.y + box.rec.height / 2 - 8;
    DrawText(option, text_x, text_y, 16, BLACK);
}

ActionBox::ActionBox() {
    char s[20] = "Insert";
    Rectangle a = {6, 90, 293.9, 44.6};
    BOX box;
    box.setRec(a);
    box.setOutline(BLACK);
    box.setColor(WHITE);
    action.setBox(box);
    action.setOption(s);
}
void ActionBox::draw() {
    action.draw();
}