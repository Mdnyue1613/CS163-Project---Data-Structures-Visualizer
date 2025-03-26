#include "../header/DS2.h"

DS2::DS2(void) {
    // Title Box
    Color titleBoxColor = {248, 240, 240, 255};
    char titleName[] = "CHAINING HASH TABLE";
    titleBox = PTitleBox(0, 0, 1200, 83, 6, titleBoxColor, BLACK, titleName, 30);

    // Function Area
    Color functionAreaBackgroundColor = {75, 189, 224, 255};
    functionArea = PFunctionArea(0, 86, 307, 296, functionAreaBackgroundColor);
}

void DS2::draw(void) {
    // Draw the title of Data Structure 1
    titleBox.draw();

    // Draw the function area and take request from user
    vector<string> request = functionArea.draw();

    // Operate request
    if(request[0] == "initialize" && request[1] == "random") {
        randomInitialize();
    }

    // Draw Data Structure
    // doublyLinkedList.draw();
}

void DS2::randomInitialize() {
    // doublyLinkedList.random(10);
}