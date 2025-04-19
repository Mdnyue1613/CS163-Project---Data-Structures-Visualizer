#pragma once
#include <raylib.h>
#include "PTitleBox.h"
#include "PSwitchBox.h"
#include "PInputBox.h"
#include "PIconBox.h"
#include "PConstants.h"
#include "tinyfiledialogs.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct DInitializeMenu {
    int x, y, width, height;
    PSwitchBox Mode;
    PInputBox InputBox;
    PInputBox ModeNumberInputBox;
    PInputBox TableSizeInputBox;
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

    DInitializeMenu(void); // Empty initialize
    ~DInitializeMenu(void); // Delete used memories
    DInitializeMenu(int x, int y, int width, int height); // Initialize with size of the background
    DInitializeMenu(Vector2 pos, Vector2 size); // Initialize Vector2 version
    void draw(void);
    vector<string> update(void);
    void prepare(void);

};