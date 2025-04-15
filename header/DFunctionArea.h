#pragma once
#include <raylib.h>
#include "PTitleBox.h"
#include "DInitializeMenu.h"
#include "DInsertMenu.h"
#include "PConstants.h"
#include <string>
#include <vector>
using namespace std;

struct DFunctionArea {
    Rectangle background;
    bool initialize;
    DInitializeMenu menuInitialize;
    DInsertMenu menuInsert;
    PSwitchBox state;

    enum StateID {
        Initialize,
        Insert
    };
    
    DFunctionArea(void); // initialize
    DFunctionArea(int x, int y, int width, int height); // initialize with parameters
    DFunctionArea(Vector2 pos, Vector2 size); // initialize with parameters: using pair
    vector<string> draw(void); // return the current request from the user
    void prepare(void);
};