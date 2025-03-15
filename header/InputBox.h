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
    void setState(); // update isClick
    void setTextBox(BOX box); // set box
    void afterMove(); // handle when the box covers the mouse
    void afterClick(); // handle when the box is being chosen
    void draw(); // update
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
