#pragma once
#include <raylib.h>
#include "PTitleBox.h"
#include "PSwitchBox.h"
#include "PInputBox.h"
#include "PIconBox.h"
#include "PConstants.h"
#include <string>
#include <vector>
using namespace std;

struct PInitializeMenu {
    int x, y, width, height;
    PSwitchBox Mode;
    PInputBox InputBox;
    PTitleBox GO;
    PIconBox InputFileBox;
    int currentMode;

    enum ModeID {
        Random,
        Input
    };

    string inputBoxTitle[2] = {
        "Number of nodes",
        "Enter a list"
    };

    PInitializeMenu(void); // Empty initialize
    ~PInitializeMenu(void); // Delete used memories
    PInitializeMenu(int x, int y, int width, int height); // Initialize with size of the background
    PInitializeMenu(Vector2 pos, Vector2 size); // Initialize Vector2 version
    void draw(void);
    vector<string> update(void);
    void prepare(void);
};