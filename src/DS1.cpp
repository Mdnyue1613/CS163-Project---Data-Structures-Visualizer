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

    // Initialize request
    if(request[0] == "initialize") {
        operateInitialize(request);
    }

    // Draw Data Structure
    doublyLinkedList.draw();
}

void DS1::operateInitialize(vector<string>& request) {
    // Random initializer
    if(request[1] == "random") {
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
    else if(request[1] == "input") {
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
}

void DS1::randomInitialize(int x) {
    doublyLinkedList.random(x);
}

vector<int> DS1::stringToVectorInt(string& s) {
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
                PConstants::PLimit::intData % 10 < s[i] - '0')
                valid = false;
            lastValue = lastValue * 10 + s[i] - '0';
        }
        else {
            return vector<int>(0);
        }
    }
    if(hasContent)
        res.push_back(lastValue);
    return res;
}

void DS1::vectorIntInitialize(vector<int>& vi) {
    doublyLinkedList.build(vi);
}