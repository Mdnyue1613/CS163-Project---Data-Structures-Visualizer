#pragma once
#include "raylib.h"

struct BOX
{
    Rectangle rec;
    Color color, outlineColor;
    bool isMove(); // return true if the mouse is in the box
    bool isClick(); // return true if user click on the box
    void setColor(Color color); // set color
    void setOutline(Color color); // set outline color
    void setSize(float x,  float y, int width, int height); // set size
    void setRec(Rectangle rec); // set rectangle
    void draw(); // draw
};