#include "../header/DS3.h"

DS3::DS3() : 
    functionArea(0, 86, 307, 296, {75, 189, 224, 255}) {
    // Title Box
    Color titleBoxColor = {248, 240, 240, 255};
    char titleName[] = "AVL TREE";
    titleBox = PTitleBox(0, 0, 1200, 83, 6, titleBoxColor, BLACK, titleName, 30);
    isAnimation = false;
}

void DS3::draw() {
    // Draw the title of Data Structure 1
    titleBox.draw();
    // Draw the function area and take request from user
    vector<string> request = functionArea.draw(isAnimation == false);
    inputBox.draw(isAnimation == false);
    // Operate request
    if(request[0] == "initialize" && request[1] == "random") {
        Tree.isInit = 1;
        RandomInitialize();
    }

    else if(request[0] == "insert" && request[1] == "Insert") {
        Tree.isInsert = 1;
        Insert();
    }

    else if(request[0] == "delete") {
        if (request[1] == "delete") {
            Tree.isDelete = 1;
            Delete();
        }
        else if (request[1] == "clear") {
            Tree.removeAll();
        }
    }

    else if(request[0] == "find" && request[1] == "Find") {
        Tree.isFind = 1;
        // Find();
    }
    isAnimation = (Tree.isInit || Tree.isInsert || Tree.isDelete || Tree.isFind);
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
    if(inputBox.inputData != "") Tree.insertNode(Tree.TreeRoot, nullptr, inputBox.data);
    inputBox.data = 0;
    inputBox.inputData = "";
}

void DS3::Delete() {
    if(inputBox.inputData != "") Tree.FindDeleteNode(Tree.TreeRoot, nullptr, inputBox.data);
    inputBox.data = 0;
    inputBox.inputData = "";
}

