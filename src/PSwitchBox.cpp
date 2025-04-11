#include "../header/PSwitchBox.h"

PSwitchBox::SwitchArrow::SwitchArrow(void) {}

PSwitchBox::SwitchArrow::SwitchArrow(Vector2 a, Vector2 b, Vector2 c) :
    arrowHead({a, b, c}) {}

bool PSwitchBox::SwitchArrow::isMouseOn(void) {
    return CheckCollisionPointTriangle(GetMousePosition(), arrowHead[0], arrowHead[1], arrowHead[2]);
}

bool PSwitchBox::SwitchArrow::isClick(void) {
    return isMouseOn() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void PSwitchBox::SwitchArrow::draw(void) {
    if(isMouseOn())
        DrawTriangle(arrowHead[0], arrowHead[1], arrowHead[2], PConstants::PSwitchBox::arrowColor2);
    else
        DrawTriangle(arrowHead[0], arrowHead[1], arrowHead[2], PConstants::PSwitchBox::arrowColor1);
}

PSwitchBox::PSwitchBox(void) {}

PSwitchBox::PSwitchBox(Vector2 pos, Vector2 size, int outThickness, Color inColor, Color outColor, vector<string> options, int textSize) :
    PTitleBox(pos, size, outThickness, inColor, outColor, options[0], textSize),
    optionID(0),
    options(options),
    leftArrowHead(Vector2{pos.x + PConstants::PSwitchBox::arrowHeadSpace, pos.y + size.y / 2.f}, 
        Vector2{pos.x + PConstants::PSwitchBox::arrowHeadSpace + PConstants::PSwitchBox::arrowHeadWidth, pos.y + size.y / 2.f + PConstants::PSwitchBox::arrowHeadHeight},
        Vector2{pos.x + PConstants::PSwitchBox::arrowHeadSpace + PConstants::PSwitchBox::arrowHeadWidth, pos.y + size.y / 2.f - PConstants::PSwitchBox::arrowHeadHeight}),
    rightArrowHead(Vector2{pos.x + size.x - PConstants::PSwitchBox::arrowHeadSpace, pos.y + size.y / 2.f}, 
        Vector2{pos.x + size.x - PConstants::PSwitchBox::arrowHeadSpace - PConstants::PSwitchBox::arrowHeadWidth, pos.y + size.y / 2.f - PConstants::PSwitchBox::arrowHeadHeight},
        Vector2{pos.x + size.x - PConstants::PSwitchBox::arrowHeadSpace - PConstants::PSwitchBox::arrowHeadWidth, pos.y + size.y / 2.f + PConstants::PSwitchBox::arrowHeadHeight}) {}

void PSwitchBox::draw(void) {
    PTitleBox::draw();
    leftArrowHead.draw();
    rightArrowHead.draw();
}

int PSwitchBox::update(void) {
    bool updated = false;
    if(leftArrowHead.isClick()) {
        optionID = (optionID == 0 ? (int)options.size() - 1 : optionID - 1);
        updated = true;
    }
    if(rightArrowHead.isClick()) {
        optionID = (optionID == (int)options.size() - 1 ? 0 : optionID + 1);
        updated = true;
    }
    if(updated) {
        for(int i = 0; i < (int)options[optionID].size(); i++)
            title[i] = options[optionID][i];
        title[options[optionID].size()] = '\0';
    }
    return optionID;
}