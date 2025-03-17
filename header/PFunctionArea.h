#pragma once
#include <raylib.h>
#include "PTitleBox.h"
#include "PInitializeMenu.h"
#include <string>
#include <vector>
using namespace std;

struct PFunctionArea {
    Rectangle background;
    Color backgroundColor;
    bool initialize;
    
    PFunctionArea(void); // initialize
    PFunctionArea(int x, int y, int width, int height, Color backColor); // initialize with parameters
    vector<string> draw(void); // return the current request from the user
};