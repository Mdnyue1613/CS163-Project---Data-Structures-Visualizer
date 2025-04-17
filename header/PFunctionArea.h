#pragma once
#include <raylib.h>
#include "PTitleBox.h"
#include "PInitializeMenu.h"
#include "PConstants.h"
#include "PInsertMenu.h"
#include "PRemoveMenu.h"
#include "PSearchMenu.h"
#include "PUpdateMenu.h"
#include <string>
#include <vector>
using namespace std;

struct PFunctionArea {
    Rectangle background;
    PInitializeMenu menuInitialize;
    PInsertMenu menuInsert;
    PRemoveMenu menuRemove;
    PSearchMenu menuSearch;
    PUpdateMenu menuUpdate;
    PSwitchBox state;
    int currentMode;

    enum StateID {
        Initialize,
        Insert,
        Remove,
        Search,
        Update
    };
    
    PFunctionArea(void); // initialize
    PFunctionArea(int x, int y, int width, int height); // initialize with parameters
    PFunctionArea(Vector2 pos, Vector2 size); // initialize with parameters: using Vector2
    void draw(void); // draw
    vector<string> update(void); // return the current request from the user
    void prepare(void);
};