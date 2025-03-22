#include "../header/PTitleBox.h"

PTitleBox::PTitleBox(void) {
}

PTitleBox::PTitleBox(int x, int y, int width, int height, int outThickness, Color inColor, Color outColor, char name[50], int nameSize)
: PBOX::PBOX(x, y, width, height, outThickness, inColor, outColor) {
    strcpy(title, name);
    titleSize = nameSize;
}

PTitleBox::PTitleBox(Vector2 pos, Vector2 size, int outThickness, Color inColor, Color outColor, char name[50], int nameSize) :
 PBOX::PBOX(pos, size, outThickness, inColor, outColor) {
    strcpy(title, name);
    titleSize = nameSize;
}

void PTitleBox::draw(void) {
    PBOX::draw();
    int textWidth = MeasureText(title, titleSize);
    DrawText(title, rec.x + (rec.width - textWidth) / 2, rec.y + (rec.height - titleSize) / 2, titleSize, BLACK);
}