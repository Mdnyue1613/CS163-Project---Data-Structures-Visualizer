#pragma once
#include <raylib.h>
#include "PInputBox.h"
#include "PConstants.h"
#include <string>
#include <vector>
using namespace std;

struct PSearchMenu {
    float x, y, width, height; // position and size of the menu
    PInputBox InputBox; // input box
    PTitleBox GO; // go button

    PSearchMenu(void); // initialize
    PSearchMenu(float x, float y, float width, float height); // initialize with parameters
    PSearchMenu(Vector2 pos, Vector2 size); // initialize with parameters: using Vector2
    void draw(void); // draw
    vector<string> update(void); // return the current request from the user
};