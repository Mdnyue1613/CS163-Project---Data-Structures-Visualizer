#include "../header/Hashtable.h"
#include "../header/PConstants.h"
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
    DrawRectangleLines(drawX, drawY, scaledSize, scaledSize, BLACK);

    // Vẽ chữ vào giữa ô vuông
    std::string text = std::to_string(value);
    string index = to_string(id);
    int textWidth = MeasureText(text.c_str(), TEXT_SIZE * scale);
    DrawText(text.c_str(), drawX + (scaledSize - textWidth) / 2, drawY + (scaledSize - TEXT_SIZE * scale) / 2, TEXT_SIZE * scale, BLACK);

    // Get the width of index number
    float width = MeasureText(index.c_str(), NUMBER_SIZE);
    //Draw index of the square
    DrawText(index.c_str(), x + (CELL_SIZE - width)/2, y - 5 - NUMBER_SIZE, NUMBER_SIZE*scale, RED);
}
void Hashtable::random(int number)
{
    table.resize(number);
    int div=1;
    int mod=0;
    for (int i=0; i<number; i++){
        int newid = i%15;
        table[i].value = rd.random(1,100);
        if (i>=15*div){
            mod++;
            div++;
        }
        table[i].setPosition(400 + newid*10 + CELL_SIZE*table[i].scale*newid, 250+ CELL_SIZE * table[i].scale*mod + 30*mod);
        table[i].id = i;
    }
}

void Hashtable::draw()
{
    for (int i=0; i<table.size(); i++){

        table[i].draw();
    }
}
void Hashtable::build (vector<int>& vi)  
{

}