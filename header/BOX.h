#include "raylib.h"

struct BOX
{
    Rectangle rec;
    Color color, outlineColor;
    bool isMove();
    bool isClick();
    void setColor(Color color);
    void setOutline(Color color);
    void setSize(float x,  float y, int width, int height);
    void setRec(Rectangle rec);
    void draw();

};