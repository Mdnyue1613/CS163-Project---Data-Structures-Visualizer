#pragma once
#include <raylib.h>
#include "PTitleBox.h"
#include "PInitializeMenu.h"
#include "Constants.h"
#include <string>
#include <vector>
using namespace std;

struct PFunctionArea {
    Rectangle background;
    Color backgroundColor;
    bool initialize;
    PInitializeMenu menuInitialize;
    
    PFunctionArea(void); // initialize
    PFunctionArea(int x, int y, int width, int height, Color backColor); // initialize with parameters
    PFunctionArea(Vector2 pos, Vector2 size, Color backColor); // initialize with parameters: using pair
    vector<string> draw(void); // return the current request from the user
};