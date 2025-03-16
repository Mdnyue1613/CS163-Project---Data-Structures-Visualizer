#include "../header/PTitleBox.h"

PTitleBox::PTitleBox(void) {
}

PTitleBox::PTitleBox(int x, int y, int width, int height, int outThickness, Color inColor, Color outColor) {
    rec.x = x;
    rec.y = y;
    rec.width = width;
    rec.height = height;
    outlineThickness = outThickness;
    color = inColor;
    outlineColor = outColor;
}