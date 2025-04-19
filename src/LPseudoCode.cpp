#include"../header/LPseudoCode.h"

LPseudoCode::LPseudoCode() :
backGround({PConstants::PseudoCodeArea::pos.x, PConstants::PseudoCodeArea::pos.y, PConstants::PseudoCodeArea::size.x, PConstants::PseudoCodeArea::size.y}) {};

LPseudoCode::LPseudoCode(vector<string> pseudoCode, int numLine):
backGround({PConstants::PseudoCodeArea::pos.x, PConstants::PseudoCodeArea::pos.y, PConstants::PseudoCodeArea::size.x, PConstants::PseudoCodeArea::size.y}) {
    this->numLine = numLine;
    for(int i = 0; i < numLine; i++) {
        codeLine.push_back({backGround.x, backGround.y + i * (PConstants::PseudoCodeArea::spaceY + fontSize) + PConstants::PseudoCodeArea::spaceY, backGround.width, PConstants::PseudoCodeArea::fontSize});
        codeLineColor.push_back(backGroundColor);
    }
    this->pseudoCode = pseudoCode;
}

void LPseudoCode::update(int line) {
    for (auto& c : this->codeLineColor) {
        c = backGroundColor;
    }
    if(line >= 0 && line < numLine) {
        this->codeLineColor[line] = highlightCodeColor;
    }
}

void LPseudoCode::draw() {
    DrawRectangleRec(backGround, backGroundColor);
    for(int i = 0; i < numLine; i++) {
        DrawRectangleRec(codeLine[i], codeLineColor[i]);
        DrawText(pseudoCode[i].c_str(), codeLine[i].x + PConstants::PseudoCodeArea::spaceX, codeLine[i].y, fontSize, textColor);
    }
}

void LPseudoCode::setPseudoCode(vector<string> pseudoCode, int numline) {
    this->numLine = numline;
    this->pseudoCode = pseudoCode;
    codeLine.clear();
    codeLineColor.clear();
    for(int i = 0; i < numLine; i++) {
        codeLine.push_back({backGround.x, backGround.y + i * (PConstants::PseudoCodeArea::spaceY + fontSize) + PConstants::PseudoCodeArea::spaceY, backGround.width, PConstants::PseudoCodeArea::fontSize});
        codeLineColor.push_back(backGroundColor);
    }
}