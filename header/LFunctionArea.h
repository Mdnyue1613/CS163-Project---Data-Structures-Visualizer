#pragma once
#include<raylib.h>
#include<vector>
#include<string>
#include<cstring>
#include"LInitialize.h"
#include "LInsertMenu.h"
using namespace std;

struct LFunctionArea {
    Rectangle background;
    Color backgroundColor;
    int ChooseAction;

    LFunctionArea();
    LFunctionArea(int x, int y, int width, int height, Color color);
    vector<string> draw();
};