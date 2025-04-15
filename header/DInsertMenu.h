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

struct DInsertMenu {
    int x, y, width, height;
    PSwitchBox Mode;
    PInputBox InputBox;
    PTitleBox GO;
    PIconBox InputFileBox;
    int currentMode;

    enum ModeID {
        Single,
        List
    };

    string inputBoxTitle[2] = {
        "Value",
        "Enter a list"
    };

    DInsertMenu(void); // Empty initialize
    ~DInsertMenu(void); // Delete used memories
    DInsertMenu(int x, int y, int width, int height); // Initialize with size of the background
    DInsertMenu(Vector2 pos, Vector2 size); // Initialize Vector2 version
    void draw(void);
    vector<string> update(void);
    void prepare(void);

};