#include "../header/DS3.h"

DS3::DS3() : 
    functionArea(0, 86, 307, 296, {75, 189, 224, 255}) {
    // Title Box
    Color titleBoxColor = {248, 240, 240, 255};
    char titleName[] = "AVL TREE";
    titleBox = PTitleBox(0, 0, 1200, 83, 6, titleBoxColor, BLACK, titleName, 30);
    isAnimation = false;
}

void DS3::prepare() {
    functionArea.prepare();
}

void DS3::draw() {
    // Draw the title of Data Structure 1
    titleBox.draw();
    // Draw the function area and take request from user
    vector<string> request = functionArea.draw(isAnimation == false);
    // Operate request
    if(request[0] == "initialize" && request[1] == "random") {
        Tree.isInit = 1;
        if(request.size() == 2)
            RandomInitialize("");
        else if(request.size() == 3)
            RandomInitialize(request[2]);
    }

    else if(request[0] == "insert" && request[1] == "Insert") {
        if(request.size() == 3) {
            Tree.isInsert = 1;
            Insert(request[2]);
        }
    }

    else if(request[0] == "delete") {
        if (request[1] == "delete" && request.size() == 3) {
            Tree.isDelete = 1;
            Delete(request[2]);
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
void DS3::RandomInitialize(string num) {
    int val;
    if (num == "") {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(7, 15);
        int numNode = dist(gen);
        val = numNode;
    }
    else {
        for (char c:num) {
            if(c < '0' || c > '9') {
                Tree.isInit = 0;
                return;
            }
        }
        val = stoi(num);
    }
    Tree.random(val);
}

void DS3::Insert(string num) {
    int val;
    for (auto c : num) {
        if (c < '0' || c  > '9') {
            Tree.isDelete = 0;
            return;
        }
    }
    val = stoi(num);
    Tree.insertNode(Tree.TreeRoot, nullptr, val);
}

void DS3::Delete(string num) {
    int val;
    for (auto c : num) {
        if (c < '0' || c  > '9') {
            Tree.isDelete = 0;
            return;
        }
    }
    val = stoi(num);
    Tree.FindDeleteNode(Tree.TreeRoot, nullptr, val);
}

