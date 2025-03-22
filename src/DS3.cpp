#include "../header/DS3.h"

DS3::DS3() :
    functionArea(Constants::functionArea::pos, Constants::functionArea::size, Constants::functionArea::boxColor),
    titleBox(Constants::titleBar::pos, Constants::titleBar::size, Constants::titleBar::outlineThickness, Constants::titleBar::boxColor, Constants::titleBar::outlineColor, "AVL TREE", Constants::titleBar::textSize) {
}

void DS3::draw() {
    // Draw the title of Data Structure 1
    titleBox.draw();

    // Draw the function area and take request from user
    vector<string> request = functionArea.draw();

    // Operate request
    if(request[0] == "initialize" && request[1] == "random") {
        RandomInitialize();
    }

    // Draw Data Structure
    Tree.draw();
}
void DS3::RandomInitialize() {
    Tree.random(10);
}