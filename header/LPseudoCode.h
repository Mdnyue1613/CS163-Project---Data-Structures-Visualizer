#pragma once
#include<raylib.h>
#include<cstring>
#include<string>
#include<vector>
#include"PConstants.h"

using namespace std;

struct LPseudoCode{
    Rectangle backGround;
    const int numLine = 6;
    vector<Rectangle> codeLine;
    vector<Color> codeLineColor;
    vector<string> pseudoCode;
    Color backGroundColor = PConstants::PseudoCodeArea::backgroundColor;
    Color highlightCodeColor = PConstants::PseudoCodeArea::highlightCodeColor;
    Color textColor = PConstants::PseudoCodeArea::textColor;
    float fontSize = PConstants::PseudoCodeArea::fontSize;
    LPseudoCode();
    void update(int line);
    void draw();
};