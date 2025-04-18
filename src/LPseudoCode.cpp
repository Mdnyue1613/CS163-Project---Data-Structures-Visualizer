#include"../header/LPseudoCode.h"

LPseudoCode::LPseudoCode():
backGround({PConstants::PseudoCodeArea::pos.x, PConstants::PseudoCodeArea::pos.y, PConstants::PseudoCodeArea::size.x, PConstants::PseudoCodeArea::size.y}) {
    for(int i = 0; i < numLine; i++) {
        codeLine.push_back({backGround.x, backGround.y + i * (PConstants::PseudoCodeArea::spaceY + fontSize) + PConstants::PseudoCodeArea::spaceY, backGround.width, PConstants::PseudoCodeArea::fontSize});
        codeLineColor.push_back(backGroundColor);
    }
    pseudoCode = {"check balance factor:", 
                "   case 1: this.rotateRight", 
                "   case 2: this.rotateLeft", 
                "   case 3: this.left.rotateLeft, this.rotateRight",
                "   case 4: this.right.rotateRight, this.rotateLeft",
                "   this is balance"};
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