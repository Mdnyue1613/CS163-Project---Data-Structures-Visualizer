#include "../header/DS2.h"

DS2::DS2(void) :
    functionArea(PConstants::PFunctionArea::pos, PConstants::PFunctionArea::size),
    titleBox(PConstants::PTitleBar::pos, PConstants::PTitleBar::size, PConstants::PTitleBar::outlineThickness, PConstants::PTitleBar::boxColor, PConstants::PTitleBar::outlineColor, "HASH TABLE CHAINING", PConstants::PTitleBar::textSize),
    hashtable() {}

DS2::~DS2(void) {
    UnloadTexture(icon);
}

void DS2::draw(void) {
    // Draw the title of Data Structure 2
    titleBox.draw();

    // Draw the function area and take request from user
    vector<string> request = functionArea.update();
    functionArea.draw();

    // Initialize request
    if(request[0] == "initialize") {
        operateInitialize(request);
    }

    // DrawTexture(icon, 0, 0, WHITE);

    // Draw Data Structure
    hashtable.draw();
}

void DS2::operateInitialize(vector<string>& request) {
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

void DS2::randomInitialize(int x) {
    hashtable.random(x);
}

vector<int> DS2::stringToVectorInt(string& s) {
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

void DS2::vectorIntInitialize(vector<int>& vi) {
    hashtable.build(vi);
}

void DS2::loadTextures(void) {
    Image image = LoadImage("Assets/Images/PFileIcon.png");
    icon = LoadTextureFromImage(image);
    UnloadImage(image);
}