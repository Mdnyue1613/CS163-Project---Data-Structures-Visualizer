#pragma once
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include"PTitleBox.h"

struct LInitializeMenu{
    const int boxHeight = 45;
    const int verticalSpace = 5;
    const int horizontalSpace = 5;
    const int boxOutlineThickness = 2;

    int x, y, width, height, characterSize;
    PTitleBox Name, Mode, GO;
    LInitializeMenu();
    LInitializeMenu(int x, int y, int width, int height, int characterSize);
    string draw();
};