#pragma once
#include "PBOX.h"
#include <string>
using namespace std;

struct PTitleBox : PBOX {
    char title[50];
    int titleSize;

    PTitleBox(void);
    PTitleBox(int x, int y, int width, int height, int outThickness, Color inColor, Color outColor, string name, int nameSize); // initialize with parameters
    PTitleBox(Vector2 pos, Vector2 size, int outThickness, Color inColor, Color outColor, string name, int nameSize); // initialize with Vecter2 paramenters
    void draw(void);
};