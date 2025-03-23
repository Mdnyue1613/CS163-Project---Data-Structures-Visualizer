#pragma once
#include "raylib.h"
#include "PConstants.h"

struct PBOX
{
    Rectangle rec;
    Color color, outlineColor;
    int outlineThickness;

    PBOX(void); // initialize
    PBOX(int x, int y, int width, int height, int outThickness, Color inColor, Color outColor); // initialize with parameters
    PBOX(Vector2 pos, Vector2 size, int outThickness, Color inColor, Color outColor); // initialize with Vecter2 parementers
    bool isMove();
    bool isClick();
    void setColor(Color color);
    void setOutlineColor(Color color);
    void setOutlineThickness(int thickness);
    void setSize(float x,  float y, int width, int height);
    void setRec(Rectangle rec);
    void draw();
};