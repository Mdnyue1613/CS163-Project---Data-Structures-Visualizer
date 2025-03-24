#pragma once
#include "PBOX.h"
#include <string>
#include <iostream>
using namespace std;

struct PIconBox : public PBOX {
    string iconDestination;

    PIconBox(void);
    PIconBox(Vector2 pos, Vector2 size, int outThickness, Color inColor, Color outColor, string iconDestination);
    ~PIconBox(void);
    void draw(void);
};