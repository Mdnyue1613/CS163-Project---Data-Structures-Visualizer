#pragma once
#include<raylib.h>
#include<vector>
#include<string>
#include<cstring>
#include"LInitialize.h"
#include "LInsertMenu.h"
#include"LDeleteMenu.h"
#include "PSwitchBox.h"
using namespace std;

struct LFunctionArea{
    const int boxHeight = 45;
    const int verticalSpace = 5;
    const int horizontalSpace = 5;
    const int boxOutlineThickness = 2;
    Rectangle background;
    Color backgroundColor;
    int ChooseAction;
    PSwitchBox Mode; // Initialize = 0, Insert = 1, ...
    LInitializeMenu initializeMenu;
    LInsertMenu insertMenu;
    LDeleteMenu deleteMenu;
    LFunctionArea();
    LFunctionArea(int x, int y, int width, int height, Color color);
    vector<string> draw(bool active);
    void prepare();
};