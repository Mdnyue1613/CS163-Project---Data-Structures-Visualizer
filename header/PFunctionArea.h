#pragma once
#include <raylib.h>
#include "PTitleBox.h"
#include "PInitializeMenu.h"
#include "PConstants.h"
#include <string>
#include <vector>
using namespace std;

struct PFunctionArea {
    Rectangle background;
    bool initialize;
    PInitializeMenu menuInitialize;
    PSwitchBox state;

    enum StateID {
        Initialize,
        Insert
    };
    
    PFunctionArea(void); // initialize
    PFunctionArea(int x, int y, int width, int height); // initialize with parameters
    PFunctionArea(Vector2 pos, Vector2 size); // initialize with parameters: using pair
    vector<string> draw(void); // return the current request from the user
};