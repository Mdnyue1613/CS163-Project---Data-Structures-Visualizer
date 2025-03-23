#include "../header/DS1.h"

DS1::DS1(void) :
    functionArea(PConstants::PFunctionArea::pos, PConstants::PFunctionArea::size),
    titleBox(PConstants::PTitleBar::pos, PConstants::PTitleBar::size, PConstants::PTitleBar::outlineThickness, PConstants::PTitleBar::boxColor, PConstants::PTitleBar::outlineColor, "DOUBLY LINKED LIST", PConstants::PTitleBar::textSize) {
}

void DS1::draw(void) {
    // Draw the title of Data Structure 1
    titleBox.draw();

    // Draw the function area and take request from user
    vector<string> request = functionArea.draw();

    // Operate request
    if(request[0] == "initialize" && request[1] == "random") {
        randomInitialize();
    }

    // Draw Data Structure
    doublyLinkedList.draw();
}

void DS1::randomInitialize() {
    doublyLinkedList.random(10);
}