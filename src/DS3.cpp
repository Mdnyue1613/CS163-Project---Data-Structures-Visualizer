#include "../header/DS3.h"

DS3::DS3() {
    // Title Box
    Color titleBoxColor = {248, 240, 240, 255};
    char titleName[] = "AVL TREE";
    titleBox = PTitleBox(0, 0, 1200, 83, 6, titleBoxColor, BLACK, titleName, 30);

    // Function Area
    Color functionAreaBackgroundColor = {75, 189, 224, 255};
    functionArea = LFunctionArea(0, 86, 307, 296, functionAreaBackgroundColor);
}

void DS3::draw() {
    // Draw the title of Data Structure 1
    titleBox.draw();
    // Draw the function area and take request from user
    vector<string> request = functionArea.draw();
    inputBox.draw();
    // Operate request
    if(request[0] == "initialize" && request[1] == "random") {
        RandomInitialize();
    }

    // Draw Data Structure
    Tree.draw();
}
void DS3::RandomInitialize() {
    Tree.random(inputBox.data);
    inputBox.data = 0;
    inputBox.inputData = "";
}