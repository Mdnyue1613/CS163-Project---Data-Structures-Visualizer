#pragma once
#include <iostream>
#include <raylib.h>
#include "PConstants.h"
using namespace std;

struct PExplanationArea {
    Rectangle background;

    // Constructor
    PExplanationArea(void);

    // Update
    void update(void);

    // Draw
    void draw(void);
};