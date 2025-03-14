#include "../header/BOX.h"
using namespace std;

bool BOX::isMove()
{

}
bool BOX::isClick()
{

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
void BOX::draw()
{
    DrawRectangleRec(rec, color);
    DrawRectangleLinesEx(rec, 1.0, outlineColor);

}