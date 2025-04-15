#pragma once
#include <iostream>
#include <raylib.h>
#include "PConstants.h"
using namespace std;

struct PExplanationArea {
    Rectangle background;
    string content;

    // Constructor
    PExplanationArea(void);

    // Update
    void update(string text);

    // Draw
    void draw(void);
};