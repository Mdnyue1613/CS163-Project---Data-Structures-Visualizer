#include "../header/DS3.h"

DS3::DS3() : 
    functionArea(0, 86, 307, 296, {75, 189, 224, 255}),
    stepByStepMenu(PConstants::PStepByStepMenu::pos, PConstants::PStepByStepMenu::size) {
    // Title Box
    Color titleBoxColor = {248, 240, 240, 255};
    char titleName[] = "AVL TREE";
    titleBox = PTitleBox(0, 0, 1200, 83, 6, titleBoxColor, BLACK, titleName, 30);
    isAnimation = false;
}

void DS3::prepare() {
    functionArea.prepare();
    stepByStepMenu.prepare();
}

void DS3::draw() {
    // Draw the title of Data Structure 1
    titleBox.draw();
    // Draw the function area and take request from user
    vector<string> request = functionArea.draw(isAnimation == false);
    // Draw the step by step menu
    stepByStepMenu.draw();
    int stepByStepRequest = stepByStepMenu.getRequest();

    // Operate request
    if(request[0] == "initialize" && request[1] == "random") {
        Tree.isInit = 1;
        if(request.size() == 2)
            RandomInitialize("");
        else if(request.size() == 3)
            RandomInitialize(request[2]);
    }

    else if (request[0] == "initialize" && request[1] == "data") {
        if (request.size() == 3) {
            vector<int> nums = stringToVectorInt(request[2]);
            if (nums.size() > 0) {
                Tree.isInit = 1;
                vectorIntInitialize(nums);
            }
        }
    }

    else if(request[0] == "insert" && request[1] == "Insert") {
        if(request.size() == 3) {
            Tree.isInsert = 1;
            Insert(request[2]);
        }
    }

    else if(request[0] == "delete") {
        if (request[1] == "delete") {
            if (request.size() == 3) {
                if(Tree.selectionNode) {
                    request[2] = to_string(Tree.selectionNode->val);
                }
                if(request[2] != "") {
                    Delete(request[2]);
                }
            }
        }
        else if (request[1] == "clear") {
            Tree.removeAll();
        }
    }

    else if(request[0] == "find" && request[1] == "find") {
        if(request.size() == 3) {
            if(Tree.selectionNode) request[2] = to_string(Tree.selectionNode->val);
            if(request[2] != "") {
                Tree.isFind = 1;
                Find(request[2]);
            }
        }
    }
    isAnimation = (Tree.isInit || Tree.isInsert || Tree.isDelete || Tree.isFind);
    // Draw Data Structure
    if(isAnimation == false) {
        updateSelectionNode();
    }
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
    Tree.isDelete = 1;
    val = stoi(num);
    Tree.findData = val;
    Tree.FindDeleteNode(Tree.TreeRoot, nullptr, val);
}

vector<int> DS3::stringToVectorInt(string s) {
    for (auto c : s) {
        if (c != ' ') {
            if (c < '0' || c > '9') return {};
        }
    }
    vector<int> res;
    stringstream ss(s);
    string num;
    while(ss >> num) {
        res.push_back(stoi(num));
    }
    return res;
}

void DS3::vectorIntInitialize(vector<int> nums) {
    Tree.vectorIntInit(nums);
}

void DS3::updateSelectionNode() {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse = GetMousePosition();
        if(CheckCollisionPointRec(mouse, {0, 86, 307, 296})) return;
        Tree.defaultTree();
        for(auto Node : Tree.allNode) {
            if(CheckCollisionPointCircle(mouse, Node->position, Node->radius)) {
                if(Tree.selectionNode != Node) {
                    Tree.selectionNode = Node;
                    Tree.selectionNode->setColor(Tree.selectionNodeColor);
                    return;
                }
            }
        }
        Tree.selectionNode = nullptr;
    }
}

void DS3::Find(string num) {
    int val;
    for (auto c : num) {
        if (c < '0' || c  > '9') {
            Tree.isFind = 0;
            return;
        }
    }
    val = stoi(num);
    Tree.findData = val;
    Tree.findNode(Tree.TreeRoot, val);
}