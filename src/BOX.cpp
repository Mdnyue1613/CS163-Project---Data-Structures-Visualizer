#include "../header/BOX.h"
using namespace std;

bool BOX::isMove()
{
    if (CheckCollisionPointRec(GetMousePosition(), rec) == true) return true;
    return 0;
}
bool BOX::isClick()
{
    if (isMove() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return true;
    return false;
}
void BOX::setColor(Color color)
{
    this->color = color;
}
void BOX::setOutline(Color color)
{
    this -> outlineColor = color;
}
void BOX::setSize(float x,  float y, int width, int height)
{
    Rectangle a;
    a.x = x;
    a.y = y;
    a.height = height;
    a.width = width;
    this -> rec = a;
}

void BOX::setRec(Rectangle rec) {
    this->rec = rec;
}
void BOX::draw()
{
    DrawRectangleRec(rec, color);
    DrawRectangleLinesEx(rec, 2.0, outlineColor);

}