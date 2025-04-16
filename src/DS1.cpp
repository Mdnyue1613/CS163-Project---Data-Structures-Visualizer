#include "../header/DS1.h"

DS1::DS1(void) :
    functionArea(PConstants::PFunctionArea::pos, PConstants::PFunctionArea::size),
    stepByStepMenu(PConstants::PStepByStepMenu::pos, PConstants::PStepByStepMenu::size),
    titleBox(PConstants::PTitleBar::pos, PConstants::PTitleBar::size, PConstants::PTitleBar::outlineThickness, PConstants::PTitleBar::boxColor, PConstants::PTitleBar::outlineColor, "DOUBLY LINKED LIST", PConstants::PTitleBar::textSize),
    taskManagement(),
    randomGenerator(),
    explanationArea() {
        doublyLinkedList = new DoublyLinkedList();
        animationManagement = PDSAnimation(doublyLinkedList, &taskManagement);
    }

DS1::~DS1(void) {
    delete doublyLinkedList;
}

void DS1::prepare(void) {
    functionArea.prepare();
    stepByStepMenu.prepare();
}

void DS1::update(void) {
    // Take requests from user and put it into queue, and update the function area
    if(taskManagement.takeRequest(functionArea.update())) {
        animationManagement.reset();
    }

    // Update step-by-step menu
    stepByStepMenu.update();
    int stepRequest = stepByStepMenu.getRequest();

    // Get current request
    int type = taskManagement.getTaskType();
    vector<string> request = taskManagement.getTask();

    // Explanation
    string explanationText;

    // Initializing request
    if(type == Initialize) {
        bool done = operateInitialize(request, stepRequest, explanationText);
        if(done) taskManagement.endTask();
    }
    // Inserting request
    else if(type == Insert) {
        bool done = operateInsert(request, stepRequest, explanationText);
        if(done) taskManagement.endTask();
    }
    else if(type == Remove) {
        bool done = operateRemove(request, stepRequest, explanationText);
        if(done) taskManagement.endTask();
    }
    else if(type == Search) {
        bool done = operateSearch(request, stepRequest, explanationText);
        if(done) taskManagement.endTask();
    }
    else if(type == NoTask) {
    }

    // Update explanation area
    explanationArea.update(explanationText);

    // Update linked list
    doublyLinkedList->update();
}

void DS1::draw(void) {
    // Draw the title of Data Structure 1
    titleBox.draw();

    // Draw the function area
    functionArea.draw();

    // Draw step-by-step menu
    stepByStepMenu.draw();

    // Draw explanation area
    explanationArea.draw();

    // Draw Data Structure
    doublyLinkedList->draw();
}

bool DS1::operateInitialize(vector<string>& request, int stepRequest, string& explanationText) {
    if(taskManagement.doneTask())
        return true;

    string requestType = request[1];

    // Random initializer
    if(requestType == "random") {
        // No input
        if((int)request.size() == 2) {
            // Operate request
            doublyLinkedList->randomInitializer(randomGenerator.random(1, 40));
        }
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
                doublyLinkedList->randomInitializer(inputValue);
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
    doublyLinkedList->build(vi);
}

bool DS1::operateInsert(vector<string>& request, int stepRequest, string& explanationText) {
    bool done = true;
    string requestType = request[1];

    if(requestType == "head") {
        int value = stoi(request[2]);
        done = animationManagement.insertHead(value, stepRequest, explanationText);
        doublyLinkedList = animationManagement.dataStructurePointer;
    }
    else if(requestType == "tail") {
        int value = stoi(request[2]);
        done = animationManagement.insertTail(value, stepRequest, explanationText);
        doublyLinkedList = animationManagement.dataStructurePointer;
    }
    else if(requestType == "after") {
        int position = stoi(request[2]);
        int value = stoi(request[3]);
        done = animationManagement.insertAfter(position, value, stepRequest, explanationText);
        doublyLinkedList = animationManagement.dataStructurePointer;
    }

    return done;
}

bool DS1::operateRemove(vector<string>& request, int stepRequest, string& explanationText) {
    bool done = true;
    int value = stoi(request[1]);
    done = animationManagement.remove(value, stepRequest, explanationText);
    doublyLinkedList = animationManagement.dataStructurePointer;
    return done;
}

bool DS1::operateSearch(vector<string>& request, int stepRequest, string& explanationText) {
    bool done = true;
    int value = stoi(request[1]);
    done = animationManagement.search(value, stepRequest, explanationText);
    doublyLinkedList = animationManagement.dataStructurePointer;
    return done;
}