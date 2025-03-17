#include "../header/PFunctionArea.h"

PFunctionArea::PFunctionArea(void) {
}

PFunctionArea::PFunctionArea(int x, int y, int width, int height, Color backColor) {
    background.x = x;
    background.y = y;
    background.width = width;
    background.height = height;
    backgroundColor = backColor;
}

void PFunctionArea::draw(void) {
    DrawRectangleRec(background, backgroundColor);
}