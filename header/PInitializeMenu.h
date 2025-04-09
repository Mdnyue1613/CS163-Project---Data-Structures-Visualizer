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

struct PInitializeMenu {
    // Cordinates and sizes
    int x, y, width, height;

    /* Mode
    Has two modes:
    "Random" - random initializer
    "Input" - user input initializer
    */
    PSwitchBox Mode;

    /* Input Box
    In "Random" mode, takes "n" - number of nodes
    In "Input" mode, takes a list of integers
    */
    PInputBox InputBox;

    /* GO
    Send requests to the program
    */
    PTitleBox GO;

    /* InputFileBox
    Takes input file's directory
    */
    PIconBox InputFileBox;

    /* currentMode
        0 - Random mode
        1 - Input mode
    */
    int currentMode;
    enum ModeID {
        Random, // 0
        Input // 1
    };

    string inputBoxTitle[2] = {
        "Number of nodes",
        "Enter a list"
    };

    PInitializeMenu(void); // Empty initialize
    ~PInitializeMenu(void); // Delete used memories
    PInitializeMenu(int x, int y, int width, int height); // Initialize with size of the background
    PInitializeMenu(Vector2 pos, Vector2 size); // Initialize Vector2 version
    void draw(void); // Draw boxes
    vector<string> update(void); // Take user's requests
    void prepare(void); // Prepare textures
};