#pragma once
#include "PBOX.h"
#include <cstring>
using namespace std;

struct PTitleBox : PBOX {
    char title[50];
    int titleSize;

    PTitleBox(void);
    PTitleBox(int x, int y, int width, int height, int outThickness, Color inColor, Color outColor, char name[50], int nameSize);
    void draw(void);
};