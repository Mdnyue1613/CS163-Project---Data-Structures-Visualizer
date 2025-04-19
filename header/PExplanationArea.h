#pragma once
#include <iostream>
#include <raylib.h>
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