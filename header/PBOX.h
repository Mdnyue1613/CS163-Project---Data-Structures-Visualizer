#pragma once
#include "raylib.h"

struct PBOX
{
    Rectangle rec;
    Color color, outlineColor;
    int outlineThickness;
    bool isMove();
    bool isClick();
    void setColor(Color color);
    void setOutlineColor(Color color);
    void setOutlineThickness(int thickness);
    void setSize(float x,  float y, int width, int height);
    void setRec(Rectangle rec);
    void draw();
};