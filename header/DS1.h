#pragma once
#include "raylib.h"
#include "PTitleBox.h"
#include "PFunctionArea.h"
#include <string>
using namespace std;

struct DS1 {
    PTitleBox titleBox;
    PFunctionArea functionArea;

    DS1(void); // initialize
    void draw(void); // draw
};