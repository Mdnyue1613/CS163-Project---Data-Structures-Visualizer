#include "../header/PBOX.h"
PBOX::PBOX(void) {
}
PBOX::PBOX(int x, int y, int width, int height, int outThickness, Color inColor, Color outColor) {
    rec.x = x;
    rec.y = y;
    rec.width = width;
    rec.height = height;
    outlineThickness = outThickness;
    color = inColor;
    outlineColor = outColor;
}

PBOX::PBOX(Vector2 pos, Vector2 size, int outThickness, Color inColor, Color outColor) :
    rec{pos.x, pos.y, size.x, size.y}, outlineThickness(outThickness), color(inColor), outlineColor(outColor) {
}
bool PBOX::isMove() {
    return CheckCollisionPointRec(GetMousePosition(), rec);
}
bool PBOX::isClick() {
    return isMove() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
void PBOX::setColor(Color color) {
    this->color = color;
}
void PBOX::setOutlineColor(Color color) {
    this->outlineColor = color;
}
void PBOX::setOutlineThickness(int thickness) {
    outlineThickness = thickness;
}
void PBOX::setSize(float x,  float y, int width, int height) {
    rec.x = x;
    rec.y = y;
    rec.width = width;
    rec.height = height;
}
void PBOX::setRec(Rectangle rec) {
    this->rec = rec;
}
void PBOX::draw() {
    DrawRectangleRec(rec, color);
    DrawRectangleLinesEx(rec, outlineThickness, outlineColor);
}