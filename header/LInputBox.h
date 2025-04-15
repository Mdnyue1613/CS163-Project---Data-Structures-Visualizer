#pragma once
#include "raylib.h"
#include "BOX.h"
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

struct LInputBox
{   
    int posNum_x, posNum_y;
    const float posText_x = 11, posText_y = 212.3;
    int data;
    int fontText;
    string inputData;
    BOX box;
    bool isClick;
    LInputBox();
    void setState();
    void setInputBox(BOX box);
    void afterMove();
    void afterClick(bool appearLine);
    void draw(bool active);
};
