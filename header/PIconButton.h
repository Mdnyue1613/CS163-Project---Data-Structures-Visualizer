#pragma once
#include <raylib.h>
#include <raymath.h>
#include <string>
using namespace std;

struct PIconButton {
    Texture2D icon;
    Rectangle rec;
    Vector2 pos;
    Vector2 size;
    string directory;

    PIconButton(void);
    PIconButton(Vector2 pos, Vector2 size, string directory);
    ~PIconButton(void);

    void prepare(void);
    void draw(void);
    bool isMove(void);
    bool isClicked(void);
};