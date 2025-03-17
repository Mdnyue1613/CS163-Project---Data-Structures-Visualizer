#include "../header/DS1.h"

DS1::DS1(void) {
    // Title Box
    Color titleBoxColor = {248, 240, 240, 255};
    char titleName[] = "DOUBLY LINKED LIST";
    titleBox = PTitleBox(0, 0, 1200, 83, 6, titleBoxColor, BLACK, titleName, 25);

    // Function Area
    Color functionAreaBackgroundColor = {75, 189, 224, 255};
    functionArea = PFunctionArea(0, 86, 307, 296, functionAreaBackgroundColor);
}

void DS1::draw(void) {
    titleBox.draw();
    functionArea.draw();
}