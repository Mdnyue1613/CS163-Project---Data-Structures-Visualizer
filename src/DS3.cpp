#include "../header/DS3.h"

DS3::DS3() {
    // Title Box
    Color titleBoxColor = {248, 240, 240, 255};
    char titleName[] = "AVL TREE";
    titleBox = PTitleBox(0, 0, 1200, 83, 6, titleBoxColor, BLACK, titleName, 30);

    // Function Area
    Color functionAreaBackgroundColor = {75, 189, 224, 255};
    functionArea = PFunctionArea(0, 86, 307, 296, functionAreaBackgroundColor);
}

void DS3::draw() {
    functionArea.draw();
    titleBox.draw();
}
void DS3::RandomInitialize() {
    // Tree.random(10);
}