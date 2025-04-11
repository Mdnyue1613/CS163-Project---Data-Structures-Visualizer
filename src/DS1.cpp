#include "../header/DS1.h"

DS1::DS1(void) :
    functionArea(PConstants::PFunctionArea::pos, PConstants::PFunctionArea::size),
    stepByStepMenu(PConstants::PStepByStepMenu::pos, PConstants::PStepByStepMenu::size),
    titleBox(PConstants::PTitleBar::pos, PConstants::PTitleBar::size, PConstants::PTitleBar::outlineThickness, PConstants::PTitleBar::boxColor, PConstants::PTitleBar::outlineColor, "DOUBLY LINKED LIST", PConstants::PTitleBar::textSize),
    doublyLinkedList(),
    randomGenerator(),
    stepByStep(true) {}

DS1::~DS1(void) {}

void DS1::prepare(void) {
    functionArea.prepare();
    stepByStepMenu.prepare();
}

void DS1::update(void) {
    doublyLinkedList.update();

    // Take requests from user and put it into queue
    vector<string> request = functionArea.update();
    if(request[0] != "nothing") {
        taskQueue.push(request);
    }

    // Get current request
    request = (taskQueue.empty() ? vector<string>{"nothing"} : taskQueue.front());
    string requestType = (taskQueue.empty() ? "nothing" : taskQueue.front()[0]);

    // Initializing request
    if(requestType == "initialize") {
        bool done = operateInitialize(request);
        if(done) {
            taskQueue.pop();
        }
    }
    // Inserting request
    else if(requestType == "insert") {
        bool done = operateInsert(request);
        if(done) {
            taskQueue.pop();
        }
    }
    else if(requestType == "delete") {

    }
    else if(requestType == "search") {

    }
    else {

    }
}

void DS1::draw(void) {
    // Draw the title of Data Structure 1
    titleBox.draw();

    // Draw the function area
    functionArea.draw();

    // Draw buttons for step-by-step function
    stepByStepMenu.draw();

    // Draw Data Structure
    doublyLinkedList.draw();
}

bool DS1::operateInitialize(vector<string>& request) {
    string requestType = request[1];

    // Random initializer
    if(requestType == "random") {
        // No input
        if((int)request.size() == 2)
            // Operate request
            randomInitialize(randomGenerator.random(1, 20));
        // With input
        else {
            // Check if the input is valid
            bool valid = (int)request[2].size() < 3; // integers < 100
            for(int i = 0; i < (int)request[2].size() && valid; i++) {
                valid &= '0' <= request[2][i] && request[2][i] <= '9';
            }
            if(valid) {
                // Operate request
                int inputValue = stoi(request[2]);
                randomInitialize(inputValue);
            }
            else {
                // Announce to the user that the input is not valid
            }
        }
    }
    // Input initializer
    else if(requestType == "input") {
        // Check if the input content is valid
        vector<int> inputContent = stringToVectorInt(request[2]);
        if((int)inputContent.size() > 0) {
            // Operate request
            vectorIntInitialize(inputContent);
        }
        else {
            // Announce to the user that the input is not valid
        }
    }

    return true;
}

void DS1::randomInitialize(int x) {
    doublyLinkedList.randomInitializer(x);
}

vector<int> DS1::stringToVectorInt(string& s) {
    /*
        Convert a string into a vertor of integers
    */

    // Store result
    vector<int> res(0);

    bool hasContent = false;
    bool valid = true;
    int lastValue = 0;
    for(int i = 0; i < (int)s.size() && valid; i++) {
        if(s[i] == ' ') {
            if(hasContent) {
                res.push_back(lastValue);
                hasContent = false;
                lastValue = 0;
            }
        }
        else if('0' <= s[i] && s[i] <= '9') {
            hasContent = true;
            // PConstants::PLimit::intData < lastValue * 10 + s[i] - '0' --> no valid
            if(PConstants::PLimit::intData / 10 < lastValue ||
                (PConstants::PLimit::intData / 10 == lastValue && 
                PConstants::PLimit::intData % 10 < s[i] - '0'))
                valid = false;
            lastValue = lastValue * 10 + s[i] - '0';
        }
        else {
            return vector<int>(0);
        }
    }
    if(hasContent)
        res.push_back(lastValue);
    return valid ? res : vector<int>(0);
}

void DS1::vectorIntInitialize(vector<int>& vi) {
    doublyLinkedList.build(vi);
}

bool DS1::operateInsert(vector<string>& request) {
    string requestType = request[1];

    if(requestType == "head") {
        int value = stoi(request[2]);
        doublyLinkedList.insertHead(value);
    }
    else if(requestType == "tail") {
        int value = stoi(request[2]);
        doublyLinkedList.insertTail(value);
    }
    else if(requestType == "after") {
        int position = stoi(request[2]);
        int value = stoi(request[3]);
        doublyLinkedList.insertAfter(position, value); 
    }

    return true;
}