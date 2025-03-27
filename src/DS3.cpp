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
        Tree.isInit = 1;
        RandomInitialize();
        Tree.updateTreePosition();
    }

    else if(request[0] == "insert" && request[1] == "Insert") {
        Tree.isInsert = 1;
        Insert();
    }

    else if(request[0] == "delete" && request[1] == "Delete") {
        Tree.isDelete = 1;
        // Delete();
    }

    else if(request[0] == "find" && request[1] == "Find") {
        Tree.isFind = 1;
        // Find();
    }

    // Draw Data Structure
    Tree.draw();
}
void DS3::RandomInitialize() {
    if (inputBox.data == 0) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(7, 15);
        int numNode = dist(gen);
        inputBox.data = numNode;
    }
    Tree.random(inputBox.data);
    inputBox.data = 0;
    inputBox.inputData = "";
}

void DS3::Insert() {
    Tree.insertNode(Tree.TreeRoot, nullptr, inputBox.data);
    inputBox.data = 0;
    inputBox.inputData = "";
}

