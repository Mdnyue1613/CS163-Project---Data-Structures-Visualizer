#pragma once
#include "raylib.h"
#include "BOX.h"
#include <cmath>
#include <string>
#include <cstring>

struct LTextBox
{   
    int posNum_x, posNum_y;
    BOX box;
    bool isClick;
    LTextBox();
    void setState();
    void setTextBox(BOX box);
    void afterMove();
    void afterClick();
    void draw();
};

struct LOptionBox
{
    BOX box;
    char option[20];
    void setOption(char option[]);
    void setBox(BOX box);
    void draw();
};

struct ActionBox {
    LOptionBox action;
    ActionBox();
    void draw();
};
