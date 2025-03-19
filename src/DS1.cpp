#include "../header/DS1.h"

DS1::DS1(void) {
    // Title Box
    Color titleBoxColor = {248, 240, 240, 255};
    char titleName[] = "DOUBLY LINKED LIST";
    titleBox = PTitleBox(0, 0, 1200, 83, 6, titleBoxColor, BLACK, titleName, 30);

    // Function Area
    Color functionAreaBackgroundColor = {75, 189, 224, 255};
    functionArea = PFunctionArea(0, 86, 307, 296, functionAreaBackgroundColor);
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