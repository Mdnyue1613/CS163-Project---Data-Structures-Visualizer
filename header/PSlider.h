#pragma once
#include "HOBJECT.h"
using namespace std;

struct PSlider : public Slider {
    Color thumbColor;

    PSlider(void);
    PSlider(Vector2 pos, Vector2 size);
    void update(void);
    void draw(void);
    float getPercentage(void);
};