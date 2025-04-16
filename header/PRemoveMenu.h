#pragma once
#include <raylib.h>
#include "PConstants.h"
#include "PInputBox.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct PRemoveMenu {
    float x, y, width, height;
    PInputBox InputBox;
    PTitleBox GO;

    PRemoveMenu(void);
    PRemoveMenu(float x, float y, float width, float height);
    PRemoveMenu(Vector2 pos, Vector2 size);
    vector<string> update(void);
    void draw(void);
};