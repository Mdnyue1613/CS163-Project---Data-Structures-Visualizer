#pragma once
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include"PTitleBox.h"
#include"PSwitchBox.h"
#include"PInputBox.h"

struct LFindMenu {
    const int boxHeight = 45;
    const int verticalSpace = 5;
    const int horizontalSpace = 5;
    const int boxOutlineThickness = 2;

    int x, y, width, height, characterSize;
    PTitleBox Mode, GO;
    PInputBox inputBox;

    LFindMenu();
    LFindMenu(int x, int y, int width, int height, int characterSize);
    vector<string> draw(bool active);
};