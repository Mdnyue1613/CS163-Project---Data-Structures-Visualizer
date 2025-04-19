#pragma once
#include <raylib.h>
#include "PConstants.h"
#include "PInputBox.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct DRemoveMenu {
    float x, y, width, height;
    PInputBox InputBox;
    PTitleBox GO;

    DRemoveMenu(void);
    DRemoveMenu(float x, float y, float width, float height);
    DRemoveMenu(Vector2 pos, Vector2 size);
    vector<string> update(void);
    void draw(void);
};