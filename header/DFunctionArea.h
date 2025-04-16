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
    DInitializeMenu menuInitialize;
    DInsertMenu menuInsert;
    PSwitchBox state;
    int currentMode;

    enum StateID {
        Initialize,
        Insert
    };
    
    DFunctionArea(void); // initialize
    DFunctionArea(int x, int y, int width, int height); // initialize with parameters
    DFunctionArea(Vector2 pos, Vector2 size); // initialize with parameters: using pair
    void draw(void); // return the current request from the user
    vector<string> update(void);
    void prepare(void);
};