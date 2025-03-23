#include "../header/PInputBox.h"

PInputBox::BlinkingCursor::BlinkingCursor(void) {}

PInputBox::BlinkingCursor::BlinkingCursor(Vector2 pos, int height) :
    pos(Vector2{pos.x + PConstants::PCursor::leftSpace, pos.y}), height(height) {}

void PInputBox::BlinkingCursor::draw(void) {
    DrawLine(pos.x, pos.y, pos.x, pos.y + height, BLACK);
}

void PInputBox::BlinkingCursor::setX(int x) {
    pos.x = x;
}

PInputBox::PInputBox(void) : isChosen(false) {}

PInputBox::PInputBox(Vector2 pos, Vector2 size, int outThickness, Color inColor, Color outColor, string name, int nameSize) :
    PTitleBox(pos, size, outThickness, inColor, outColor, name, nameSize),
    cursor(pos, size.y), 
    isChosen(false) {}

void PInputBox::draw(void) {
    update();

    PBOX::draw();
    if(text.empty()) {
        int textWidth = MeasureText(title, titleSize);
        DrawText(title, rec.x + (rec.width - textWidth) / 2, rec.y + (rec.height - titleSize) / 2, titleSize, PConstants::PInputBox::titleColor);
    }
    else {
        DrawText(text.c_str(), rec.x + PConstants::PCursor::leftSpace, rec.y + (rec.height - titleSize) / 2, titleSize, PConstants::PInputBox::inputColor);
    }
    
    if(isMove())
        DrawInputSymbol();
    else
        ShowCursor();
    
    if(isChosen) {
        if(fmod(GetTime(), PConstants::PCursor::fullTime) < PConstants::PCursor::onTime)
            cursor.draw();
    }
}

void PInputBox::DrawInputSymbol(void) {
    HideCursor();
    int x = GetMouseX();
    int y = GetMouseY();
    DrawLine(x, y, x, y + PConstants::PCursor::height, BLACK); // Vertical line
    // Upper horizontal line
    DrawLine(x - PConstants::PCursor::width / 2, y, x + PConstants::PCursor::width / 2, y, BLACK);
    // Lower horizontal line
    DrawLine(x - PConstants::PCursor::width / 2, y + PConstants::PCursor::height, x + PConstants::PCursor::width / 2, y + PConstants::PCursor::height, BLACK);
}

void PInputBox::update(void) {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isMove())
        isChosen = false;
    if(isClick())
        isChosen = true;

    // Get input character
    int inputKey = GetCharPressed();
    while(inputKey > 0) {
        text.push_back((char)inputKey);
        inputKey = GetCharPressed();
    }

    // Get "backspace" and delete the last characters
    inputKey = GetKeyPressed();
    while(inputKey > 0) {
        if(inputKey == KEY_BACKSPACE && text.size())
            text.pop_back();
        inputKey = GetKeyPressed();
    }

    // Update x position of the blinking cursor
    cursor.setX(rec.x + PConstants::PCursor::leftSpace + MeasureText(text.c_str(), titleSize));
}

bool PInputBox::hasContent(void) {
    return (int)text.size() > 0;
}

string PInputBox::extract(void) {
    string res = text;
    text.clear();
    return res;
}