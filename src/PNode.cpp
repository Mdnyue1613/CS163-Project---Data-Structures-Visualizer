#include "../header/PNode.h"

PNode::PNode(void) :
    data(-1), pNext(nullptr), pPrev(nullptr), highlight(false), lineState(3),
    updatedPosition(false) {
    makeLabel();
    makePosition(true);
}

PNode::PNode(int data, PNode *pPrev, PNode *pNext) :
    data(data), pNext(pNext), pPrev(pPrev), highlight(false), lineState(3),
    updatedPosition(false) {
    makeLabel();
    makePosition(true);
}

void PNode::makeLabel(void) {
    string convertedData = to_string(data);
    if(convertedData.size() < 5)
        strcpy(label, convertedData.c_str());
}

void PNode::makePosition(bool isNew) {
    if(isNew) {
        PRandom randomGenerator;
        centerFrom = Vector2{1.f * randomGenerator.random(400, 1200), 1.f * randomGenerator.random(200, 800)};
    }
    // Case: The first node
    if(pPrev == nullptr) {
        center = {400.f, 200.f};
        direction = 1;
    }
    // There are some previous nodes
    else {
        float radius = PConstants::PNode::outerRadius;
        float lineLength = PConstants::PNode::lineLength;
        int preDirection = pPrev->direction;
        Vector2 preCenter = pPrev->center;
        float dist1 = 3.f * radius + lineLength; // Distance from the center of a node to the farest point of the next node;
        float dist2 = 2.f * radius + lineLength; // Distance between centers of two consecutive nodes
        
        if(preDirection == 1 && preCenter.x + dist1 < 1200.f) { // Rightward
            direction = 1;
            center = {preCenter.x + dist2, preCenter.y};
        }
        else if(preDirection == -1 && preCenter.x - dist1 > 312.f) { // Leftward
            direction = -1;
            center = {preCenter.x - dist2, preCenter.y};
        }
        else { // Downward
            direction = -preDirection;
            center = {preCenter.x, preCenter.y + dist2};
        }
    }
}

void PNode::update(void) {
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
    if(pPrev == nullptr)
        return;

    Vector2 start = pPrev->centerFrom;
    Vector2 end = centerFrom;
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    float length = Vector2Length(Vector2Subtract(end, start));
    float angle = atan2f(dy, dx);
    float perAngle = atan2f(-dx, dy);
    float radius = PConstants::PNode::innerRadius;
    float arrowWidth = PConstants::PNode::arrowWidth;

    // Update line: arrowHeadStart1 (top), arrowHeadEnd1 (top)
    arrowHeadStart1 = Vector2Add(start, {radius * cos(angle), radius * sin(angle)});
    arrowHeadEnd1 = Vector2Subtract(end, {radius * cos(angle), radius * sin(angle)});

    // Update arrow heads: 
        // Head 1:  arrowHeadStart2 (left), arrowHeadStart3 (right)
    Vector2 head1 = Vector2Add(arrowHeadStart1, {arrowWidth * cos(angle), arrowWidth * sin(angle)});
    arrowHeadStart2 = Vector2Subtract(head1, {arrowWidth / 2.f * cos(perAngle), arrowWidth / 2.f * sin(perAngle)});
    arrowHeadStart3 = Vector2Add(head1, {arrowWidth / 2.f * cos(perAngle), arrowWidth / 2.f * sin(perAngle)});

        // Head 2:  arrowHeadEnd2 (left), arrowHeadEnd3 (right)
    Vector2 head2 = Vector2Subtract(arrowHeadEnd1, {arrowWidth * cos(angle), arrowWidth * sin(angle)});
    arrowHeadEnd2 = Vector2Add(head2, {arrowWidth / 2.f * cos(perAngle), arrowWidth / 2.f * sin(perAngle)});
    arrowHeadEnd3 = Vector2Subtract(head2, {arrowWidth / 2.f * cos(perAngle), arrowWidth / 2.f * sin(perAngle)});
}

void PNode::drawLine(void) {
    const float lineThickness = PConstants::PNode::lineThickness;

    if(pPrev) {
        if(lineState != NoDraw) 
            DrawLineEx(pPrev->centerFrom, centerFrom, lineThickness, BLACK);
        if(lineState == PrevOnly || lineState == DrawAll)
            DrawTriangle(arrowHeadStart3, arrowHeadStart1, arrowHeadStart2, BLACK);
        if(lineState == NextOnly || lineState == DrawAll)
            DrawTriangle(arrowHeadEnd3, arrowHeadEnd1, arrowHeadEnd2, BLACK);
    }
}

void PNode::drawNode(void) {
    const float innerRadius = PConstants::PNode::innerRadius;
    const float outerRadius = PConstants::PNode::outerRadius;
    const float characterSize = PConstants::PNode::characterSize;

    const Color innerColor = (highlight ? PConstants::PNode::innerHighlightColor : PConstants::PNode::innerColor);
    const Color outerColor = (highlight ? PConstants::PNode::outerHighlightColor : PConstants::PNode::outerColor);
    const Color textColor = (highlight ? PConstants::PNode::textHighlightColor : PConstants::PNode::textColor);

    // Draw node
    DrawCircleV(centerFrom, innerRadius, innerColor);
    DrawRing(centerFrom, innerRadius, outerRadius, 0, 360, 30, outerColor);

    // Draw content
    DrawText(label, centerFrom.x - MeasureText(label, characterSize) / 2, centerFrom.y - characterSize / 2, characterSize, textColor);
}

void PNode::setPosition(Vector2 pos) {
    center = pos;
    updatedPosition = false;
}

void PNode::setLineState(int state) {
    lineState = state;
}

void PNode::addLineState(int state) {
    lineState |= state;
}