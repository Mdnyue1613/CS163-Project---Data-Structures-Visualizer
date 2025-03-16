#include "../header/DS1.h"

DS1::DS1(void) {
    Color titleBoxColor = {248, 240, 240, 255};
    titleBox = PTitleBox(0, 0, 1200, 83, 6, titleBoxColor, BLACK);
}

void DS1::draw(void) {
    titleBox.draw();
}