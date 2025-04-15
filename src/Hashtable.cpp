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

AnimatedSquare::AnimatedSquare(int _x, int _y, int _value) {
    x = _x;
    y = _y;
    value = _value;
    scale = 0.1f;
    appearing = true;
}

void AnimatedSquare::update() {
    if (appearing && scale < 1.0f) {
        scale += SCALE_SPEED;
        if (scale > 1.0f) scale = 1.0f;
    }
}

void AnimatedSquare::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

void AnimatedSquare::draw() {
    int scaledSize = CELL_SIZE * scale;
    int drawX = x + (CELL_SIZE - scaledSize) / 2;
    int drawY = y + (CELL_SIZE - scaledSize) / 2;
    DrawRectangle(drawX, drawY, scaledSize, scaledSize, squareColor);
    DrawRectangleLines(drawX, drawY, scaledSize, scaledSize, outlineColor);

    // Vẽ chữ vào giữa ô vuông
    string index = to_string(id);

    if(value != 0) {
        std::string text = std::to_string(value);
        int textWidth = MeasureText(text.c_str(), TEXT_SIZE * scale);
        DrawText(text.c_str(), drawX + (scaledSize - textWidth) / 2, drawY + (scaledSize - TEXT_SIZE * scale) / 2, TEXT_SIZE * scale, BLACK);
    }

    // Get the width of index number
    float width = MeasureText(index.c_str(), NUMBER_SIZE);
    //Draw index of the square
    DrawText(index.c_str(), x + (CELL_SIZE - width)/2, y - 5 - NUMBER_SIZE, NUMBER_SIZE*scale, RED);
}
void Hashtable::random(int number)
{
    vector<bool> visited(number, false);
    table.resize(number);

    const int mode = number; 

    int div = 1;
    int m = 0;

    for (int i = 0; i < number; i++) {
        int newid = i % 15;

        if (rd.random(0, 1) == 1) {
            int randomNum = rd.random(1, 100);
            int key = randomNum % mode;

            int originalKey = key;
            while (visited[key]) {
                key = (key + 1) % number;
                if (key == originalKey) break; 
            }

            if (!visited[key]) {
                table[key].value = randomNum;
                visited[key] = true;
            }
        }

        if (i >= 15 * div) {
            m++;
            div++;
        }

        table[i].setPosition(
            400 + newid * 10 + CELL_SIZE * table[i].scale * newid,
            250 + CELL_SIZE * table[i].scale * m + 30 * m
        );

        table[i].id = i;
    }
}

void Hashtable::draw()
{
    for (int i=0; i<table.size(); i++){

        table[i].draw();
    }
}

void Hashtable::build(vector<int>& vi)
{
    int number = vi.size();
    number *= 2; // bảng gấp đôi số phần tử
    table.clear();
    table.resize(number);

    vector<bool> visited(number, false);
    const int mode = number;

    for (int i = 0; i < vi.size(); i++) {
        int value = vi[i];
        int key = value % mode;
        int originalKey = key;

        while (visited[key]) {
            key = (key + 1) % number;
            if (key == originalKey) {
                cout << "Warning: Table full, could not insert " << value << std::endl;
                break;
            }
        }

        if (!visited[key]) {
            table[key].value = value;
            visited[key] = true;
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
            400 + newid * 10 + CELL_SIZE * table[i].scale * newid,
            250 + CELL_SIZE * table[i].scale * m + 30 * m
        );
    }
}

void Hashtable::insert(int value) {
    if (table.empty()) {
        cout << "Error: Table is not initialized. Call build() first.\n";
        return;
    }

    int size = table.size();
    int key = value % size;
    int originalKey = key;

    while (true) {
        // Highlight viền đỏ ô đang kiểm tra
        table[key].outlineColor = RED;
        draw(); // vẽ bảng
        EndDrawing(); 
        WaitTime(0.5f); // 0.5 giây chờ
        BeginDrawing();
        table[key].outlineColor = BLACK;

        if (table[key].value == 0) {
            // Highlight viền xanh lá cho ô cần chèn
            table[key].outlineColor = GREEN;
            draw();
            EndDrawing();
            WaitTime(0.5f);
            BeginDrawing();
            table[key].outlineColor = BLACK;

            // Thực hiện insert
            table[key].value = value;
            table[key].scale = 0.1f;
            table[key].appearing = true;

            int newid = key % 15;
            int row = key / 15;
            table[key].setPosition(
                400 + newid * 10 + CELL_SIZE * newid,
                250 + CELL_SIZE * row + 30 * row
            );

            break;
        }

        key = (key + 1) % size;
        if (key == originalKey) {
            cout << "Table is full. Cannot insert " << value <<endl;
            return;
        }
    }
}
