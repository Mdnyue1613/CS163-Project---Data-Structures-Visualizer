#include "../header/PNode.h"

PNode::PNode(void) :
    data(-1), pNext(nullptr), pPrev(nullptr), highlight(false), lPrev(), lNext(),
    updatedPosition(false), direction(1), information() {
    makePosition();
}

PNode::PNode(int data) :
    data(data), pNext(nullptr), pPrev(nullptr), highlight(false), lPrev(), lNext(),
    updatedPosition(false), direction(1), information() {
    makePosition();
}

void PNode::makePosition(void) {
    PRandom randomGenerator;
    centerFrom = {1.f * randomGenerator.random(350, 1200), 1.f * randomGenerator.random(200, 800)};
}

void PNode::makeLabel(void) {
    string convertedData = to_string(data);
    if(convertedData.size() < 5)
        strcpy(label, convertedData.c_str());
}

void PNode::update(void) {
    makeLabel();
    updatePosition();
    updateLine();
}

bool PNode::updatePosition(void) { 
    if(centerFrom.x != center.x || centerFrom.y != center.y) {
        // Distance
        float distanceX = center.x - centerFrom.x;
        float distanceY = center.y - centerFrom.y;
        float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

        // Distance in one move
        float toMove = PConstants::DS1::speed * GetFrameTime();
        float toMoveX = toMove * distanceX / distance;
        float toMoveY = toMove * distanceY / distance;

        // Has not reached the target point
        if( (centerFrom.x <= centerFrom.x + toMoveX && centerFrom.x + toMoveX < center.x) || 
            (centerFrom.x >= centerFrom.x + toMoveX && centerFrom.x + toMoveX > center.x) || 
            (centerFrom.y <= centerFrom.y + toMoveY && centerFrom.y + toMoveY < center.y) || 
            (centerFrom.y >= centerFrom.y + toMoveY && centerFrom.y + toMoveY > center.y) ) {
            centerFrom.x += toMoveX;
            centerFrom.y += toMoveY;
        }
        // Reached
        else
            centerFrom = center;
        return updatedPosition = false;
    }
    else {
        return updatedPosition = true;
    }
}

void PNode::updateLine(void) {
    // Update line to previous node (if exists)
    if(pPrev) {
        lPrev.setDirection(centerFrom, pPrev->centerFrom);
        lPrev.update();
    }
    // Update line to next node (if exists)
    if(pNext) {
        lNext.setDirection(centerFrom, pNext->centerFrom);
        lNext.update();
    } lNext.update();
}

void PNode::quickUpdate(void) {
    centerFrom = center;
}

void PNode::drawLine(void) {
    if(pNext != nullptr)
        lNext.draw();
    if(pPrev != nullptr)
        lPrev.draw();
}

void PNode::drawNode(void) {
    const float innerRadius = PConstants::PNode::innerRadius;
    const float outerRadius = PConstants::PNode::outerRadius;
    const float characterSize = PConstants::PNode::characterSize;

    const Color innerColor = ((highlight) ? PConstants::PNode::innerHighlightColor : PConstants::PNode::innerColor);
    const Color outerColor = ((highlight) ? PConstants::PNode::outerHighlightColor : PConstants::PNode::outerColor);
    const Color textColor = ((highlight) ? PConstants::PNode::textHighlightColor : PConstants::PNode::textColor);

    // Draw node
    DrawCircleV(centerFrom, innerRadius, innerColor);
    DrawRing(centerFrom, innerRadius, outerRadius, 0, 360, 30, outerColor);

    // Draw content
    DrawText(label, centerFrom.x - MeasureText(label, characterSize) / 2, centerFrom.y - characterSize / 2, characterSize, textColor);
}

void PNode::drawText(void) {
    // Prepare information
    information.clear();
    for(int i = 0; i < 5; i++) {
        if(informationState[i]) {
            if(information.size())
                information += '/';
            information += informationName[i];
        }
    }
    // Calculate
    const float textSize = PConstants::PNode::informationSize;
    const float radius = PConstants::PNode::outerRadius;
    const float space = PConstants::PNode::textSpace;
    const Color color = PConstants::PNode::informationTextColor;
    float contentWidth = MeasureText(information.c_str(), textSize);
    // Draw
    DrawText(information.c_str(), centerFrom.x - contentWidth / 2.f, centerFrom.y + radius + space, textSize, color);
}

void PNode::setPosition(Vector2 pos) {
    center = pos;
    updatedPosition = false;
}

void PNode::setHighlight(bool on) {
    highlight = on;
}

void PNode::setHighlightPrevLink(bool on) {
    lPrev.setHighlight(on);
}

void PNode::setHighlightNextLink(bool on) {
    lNext.setHighlight(on);
}

void PNode::setInformation(string information) {
    this->information = information;
}

void PNode::setInformationState(int i, bool on) {
    informationState[i] = on;
}

void PNode::resetInformationState(void) {
    for(int i = 0; i < 5; i++) {
        informationState[i] = false;
    }
}

bool PNode::positionIsUpdated(void) {
    return updatedPosition;
}