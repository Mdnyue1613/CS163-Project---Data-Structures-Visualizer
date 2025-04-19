#include "../header/Hashtable.h"
#include "../header/PConstants.h"
#include <iostream>
#include <vector>
using namespace std;
const int CELL_SIZE = 40;
const int TEXT_SIZE = 20;
const int NUMBER_SIZE = 15;
const float SCALE_SPEED = 0.05f;
const Color squareColor = {255, 227, 139, 255};
const Color traverseColor = {255, 138, 39, 255};
const Color successColor = {151, 219, 174, 255};
const Color boldNormalColor = {219, 195, 120, 255};
const Color boldTraverseColor = {209, 113, 32, 255};
const Color boldSuccessColor = {114, 166, 132, 255};


AnimatedSquare::AnimatedSquare(int _x, int _y, int _value) {
    x = _x;
    y = _y;
    value = _value;
    scale = 0.1f;
    highlight = false;
}


void AnimatedSquare::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

bool AnimatedSquare::isMove() {
    return CheckCollisionPointRec(GetMousePosition(), { (float)x, (float)y, (float)CELL_SIZE*scale, (float)CELL_SIZE*scale });
}
bool AnimatedSquare::isClick() {
    return isMove() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void AnimatedSquare::update() {
    // Update isOn
    if(isOn == false && isMove() == true) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        isOn = true;
    }
    else if(isOn == true && isMove() == false) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        isOn = false;
    }
    // Update isChoosen
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isMove()) {
        isChoosen = false;
    }
    if (isClick()) {
        isChoosen = true;
    }
    else {
        isChoosen = false;
    }
}

void AnimatedSquare::draw() {
    // Update the scale for zoom-in animation
    if (scale < 1.0f) {
        scale += SCALE_SPEED;
        if (scale > 1.0f) {
            scale = 1.0f; // Ensure scale does not exceed 1.0
        }
    }

    int scaledSize = CELL_SIZE * scale;
    int drawX = x + (CELL_SIZE - scaledSize) / 2;
    int drawY = y + (CELL_SIZE - scaledSize) / 2;
    Color cellColor = (highlight ? traverseColor : squareColor);
    if (highlightSearch) {
        cellColor = successColor;
    }
    if (isMove()) { 
        if (highlight) {
            cellColor = boldTraverseColor;
        } else if (highlightSearch) {
            cellColor = boldSuccessColor;
        } else {
            cellColor = boldNormalColor;
        }
    }
    DrawRectangle(drawX, drawY, scaledSize, scaledSize, cellColor);
    DrawRectangleLines(drawX, drawY, scaledSize, scaledSize, outlineColor);

    // draw text in the square
    string index = to_string(id);

    if (visited && !deleted) {
        std::string text = std::to_string(value);
        int textWidth = MeasureText(text.c_str(), TEXT_SIZE * scale);
        DrawText(text.c_str(), drawX + (scaledSize - textWidth) / 2, drawY + (scaledSize - TEXT_SIZE * scale) / 2, TEXT_SIZE * scale, BLACK);
    }

    // Get the width of index number
    float width = MeasureText(index.c_str(), NUMBER_SIZE);
    //Draw index of the square
    DrawText(index.c_str(), x + (CELL_SIZE - width)/2, y - 5 - NUMBER_SIZE, NUMBER_SIZE*scale, RED);
}
void Hashtable::random(int number, int size)
{
    table.clear();
    table.resize(size);

    const int mod = size; 
    
    for (int i = 0; i < number; i++) {
        int randomNum = rd.random(1, 100);
        key = randomNum % mod;
        originalKey = key;

        while (table[key].visited) {
            key = (key + 1) % size;
            if (key == originalKey) break; 
        }

        if (!table[key].visited) {
            table[key].value = randomNum;
            table[key].visited = true;
        }
    }
        int div = 1, m = 0;
        for (int i = 0; i < size; i++) {
        int newid = i % 15;
        if (i >= 15 * div) {
            m++;
            div++;
        }

        table[i].id = i;
        table[i].setPosition(
            400 + newid * (10 + CELL_SIZE),
            250 + m * (30 + CELL_SIZE)
        );
    }
    n = number;
}

void Hashtable::draw()
{
    for (int i=0; i<table.size(); i++){
        table[i].update();
        table[i].draw();
    }
}

void Hashtable::build(vector<int>& vi)
{
        int number = vi.size();
    number *= 2; // bảng gấp đôi số phần tử
    table.clear();
    table.resize(number);

    const int mod = number;

    for (int i = 0; i < vi.size(); i++) {
        int value = vi[i];
        int key = value % mod;
        int originalKey = key;

        while (table[key].visited) {
            key = (key + 1) % number;
            if (key == originalKey) {
                // Warning: Hash table is full, cannot insert more elements
                break;
            }
        }

        if (!table[key].visited) {
            table[key].value = value;
            table[key].visited = true;
        }
    }

    int div = 1, m = 0;
        for (int i = 0; i < number; i++) {
        int newid = i % 15;
        if (i >= 15 * div) {
            m++;
            div++;
        }

        table[i].id = i;
        table[i].setPosition(
            400 + newid * (10 + CELL_SIZE),
            250 + m * (30 + CELL_SIZE)
        );
    }
}

