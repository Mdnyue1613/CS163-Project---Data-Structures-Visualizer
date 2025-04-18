#pragma once
#include<raylib.h>
#include<cstring>
#include<string>
#include<vector>
#include"PConstants.h"

using namespace std;

struct LPseudoCode{
    Rectangle backGround;
    int numLine;
    vector<Rectangle> codeLine;
    vector<Color> codeLineColor;
    vector<string> pseudoCode;
    Color backGroundColor = PConstants::PseudoCodeArea::backgroundColor;
    Color highlightCodeColor = PConstants::PseudoCodeArea::highlightCodeColor;
    Color textColor = PConstants::PseudoCodeArea::textColor;
    float fontSize = PConstants::PseudoCodeArea::fontSize;
    LPseudoCode();
    LPseudoCode(LPseudoCode& other) {
        backGround = other.backGround;
        codeLine = other.codeLine;
        codeLineColor = other.codeLineColor;
        pseudoCode = other.pseudoCode;
        backGroundColor = other.backGroundColor;
        highlightCodeColor = other.highlightCodeColor;
        textColor = other.textColor;
        fontSize = other.fontSize;
    }
    LPseudoCode(vector<string> pseudoCode, int numLine);
    void update(int line);
    void draw();
};