#include "../header/PNodeLine.h"

PNodeLine::PNodeLine(void) :
    start{0, 0}, end{0, 0},
    head1{0, 0}, head2{0, 0}, head3{0, 0},
    highlight(false) {}

void PNodeLine::setDirection(Vector2 start, Vector2 end) {
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    float angle = atan2f(dy, dx);
    float radius = PConstants::PNode::innerRadius;
    float perAngle = atan2f(-dx, dy);

    // start = Vector2Add(start, {radius * cos(angle), radius * sin(angle)});
    // end = Vector2Subtract(end, {radius * cos(angle), radius * sin(angle)});

    float shiftUp = radius / 3.f;
    float shiftRight = sqrt(radius * radius - shiftUp * shiftUp);
    start = Vector2Add(start, {shiftUp * cos(perAngle) + shiftRight * cos(angle), shiftUp * sin(perAngle) + shiftRight * sin(angle)});
    end = Vector2Add(end, {shiftUp * cos(perAngle) - shiftRight * cos(angle), shiftUp * sin(perAngle) - shiftRight * sin(angle)});

    this->start = start;
    this->end = end;
}

void PNodeLine::setHighlight(bool on) {
    highlight = on;
}

void PNodeLine::update(void) {
    // No line
    if(start.x == end.x && start.y == end.y) {
        head1 = head2 = head3 = start;
        return;
    }
    // Precalculate the arrow head
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    float angle = atan2f(dy, dx);
    float perAngle = atan2f(-dx, dy);
    float arrowWidth = PConstants::PNode::arrowWidth;
    // Calculate the coordinates of the arrow head
    head1 = end;
    Vector2 head = Vector2Subtract(head1, {arrowWidth * cos(angle), arrowWidth * sin(angle)});
    head2 = Vector2Add(head, {arrowWidth / 2.f * cos(perAngle), arrowWidth / 2.f * sin(perAngle)});
    head3 = Vector2Subtract(head, {arrowWidth / 2.f * cos(perAngle), arrowWidth / 2.f * sin(perAngle)});
}

void PNodeLine::draw(void) {
    // No line
    if(start.x == end.x && start.y == end.y) {
        return;
    }
    // Draw the line and the arrow head
    const float lineThickness = PConstants::PNode::lineThickness;
    const Color color = highlight ? PConstants::PNodeLine::highlightColor : PConstants::PNodeLine::color;
    DrawLineEx(start, end, lineThickness, color);
    DrawTriangle(head3, head1, head2, color);
}