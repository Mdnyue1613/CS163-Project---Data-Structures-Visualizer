#pragma once
#include <raylib.h>
#include "PTitleBox.h"
#include "PSwitchBox.h"
#include "PInputBox.h"
#include "PConstants.h"
#include <string>
#include <vector>
using namespace std;

struct PInitializeMenu {
    int x, y, width, height;
    PSwitchBox Mode;
    PInputBox InputNumberOfNodes;
    PTitleBox GO;

    enum ModeID {
        Random,
        Input
    };

    PInitializeMenu(void); // Empty initialize
    PInitializeMenu(int x, int y, int width, int height); // Initialize with size of the background
    PInitializeMenu(Vector2 pos, Vector2 size); // Initialize Vector2 version
    vector<string> draw(void);
};