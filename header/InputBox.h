#pragma once
#include "raylib.h"
#include "BOX.h"
#include <cmath>
#include <string>
#include <cstring>

struct TextBox
{   
    int posNum_x, posNum_y;
    BOX box;
    bool isClick;
    void setState();
    void setTextBox(BOX box);
    void afterMove();
    void afterClick();
    void draw();
};

// struct OptionBox
// {
//     BOX box;
//     char option[20];
//     void draw();
//     void afterClick();
// };


// struct InputBox
// {

// };
