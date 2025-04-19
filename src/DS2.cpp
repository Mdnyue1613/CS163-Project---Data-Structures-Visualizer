#include "../header/DS2.h"
DS2::DS2(void) :
    functionArea(PConstants::PFunctionArea::pos, PConstants::PFunctionArea::size),
    stepByStepMenu(PConstants::PStepByStepMenu::pos, PConstants::PStepByStepMenu::size),
    titleBox(PConstants::PTitleBar::pos, PConstants::PTitleBar::size, PConstants::PTitleBar::outlineThickness, PConstants::PTitleBar::boxColor, PConstants::PTitleBar::outlineColor, "HASH TABLE LINEAR PROBING", PConstants::PTitleBar::textSize),
    hashtable(),
    explanationArea(),
    animationManager() {
        animationManager.dataStructurePointer = &hashtable;
        animationManager.taskManagementPointer = &taskManagement;
    }


DS2::~DS2(void) {
    UnloadTexture(icon);
}

void DS2::setStatusMessage(const string& msg, float duration) {
    statusMessage = msg;
    statusMessageTimer = duration;
    cout << "Status: " << msg << endl; // Also log to console for debugging
}

void DS2::prepare(void) {
    functionArea.prepare();
    stepByStepMenu.prepare();
}

void DS2::draw(bool darkMode) {
    if(darkMode == false) {
        PConstants::DS1::backgroundColor = WHITE;

        PConstants::PNode::innerColor = WHITE;
        PConstants::PNode::outerColor = BLACK;
        PConstants::PNode::textColor = BLACK;
        PConstants::PNode::informationTextColor = BLACK;

        PConstants::PNode::innerHighlightColor = {255, 138, 39, 255};
        PConstants::PNode::outerHighlightColor = {255, 138, 39, 255};
        PConstants::PNode::textHighlightColor = WHITE;

        PConstants::PNodeLine::color = BLACK;
        PConstants::PNodeLine::highlightColor = {255, 138, 39, 255};
    }
    else {
        PConstants::DS1::backgroundColor = BLACK;

        PConstants::PNode::innerColor = {58, 58, 58, 255};
        PConstants::PNode::outerColor = {65, 71, 79, 255};
        PConstants::PNode::textColor = {204, 204, 204, 255};
        PConstants::PNode::informationTextColor = {204, 204, 204, 255};

        PConstants::PNode::innerHighlightColor = {155, 89, 182, 255};
        PConstants::PNode::outerHighlightColor = {224, 255, 255, 255};
        PConstants::PNode::textHighlightColor = WHITE;

        PConstants::PNodeLine::color = {65, 71, 79, 255};
        PConstants::PNodeLine::highlightColor = {224, 255, 255, 255};
    }
    // Draw background
    float workSpaceX = PConstants::PFunctionArea::pos.x;
    float workSpaceY = PConstants::PTitleBar::size.y;
    float workSpaceWidth = GetScreenWidth() - workSpaceX;
    float workSpaceHeight = GetScreenHeight() - workSpaceY;
    Color backgroundColor = PConstants::DS1::backgroundColor;
    DrawRectangle(workSpaceX, workSpaceY, workSpaceWidth, workSpaceHeight, backgroundColor);

      // Draw the title of Data Structure 2
      titleBox.draw();

      // Draw explanation area
      explanationArea.draw();

      // Draw the function area
      functionArea.draw();

      // Draw the step-by-step menu
      stepByStepMenu.draw();

      // Draw Data Structure
      hashtable.draw();
}

void DS2::update(void){
    // Take requests from user and put it into queue, and update the function area
    if(taskManagement.takeRequest(functionArea.update())) {
        // Reset animation management
        animationManager.reset();
    }

    // Update step-by-step menu
    stepByStepMenu.update();
    int stepRequest = stepByStepMenu.getRequest();

    // Get current request
    vector<string> request = taskManagement.getTask();
    int taskType = taskManagement.getTaskType();


    // Explanation
    string explanationText;

    // hashtable.update();
    if(taskType == PTaskManagement::Initilize) {
        if(operateInitialize(request)) {
            taskManagement.endTask();
        }
    }
    else if(taskType == PTaskManagement::Insert) {
        if(operateInsert(request, stepRequest, explanationText)) {
            taskManagement.endTask();
        }
    }
    else if(taskType == PTaskManagement::Delete) {
        if(operateRemove(request, stepRequest, explanationText)) {
            taskManagement.endTask();
        }
    }
    else if(taskType == PTaskManagement::Search) {
        if(operateSearch(request, stepRequest, explanationText)) {
            taskManagement.endTask();
        }
    }
}

bool DS2::operateInitialize(vector<string>& request) {
    if(taskManagement.doneTask()) {
        return true;
    }
    for(string& s : request)
        cout << s << ' ';
    cout << '\n';
    // Random initializer
    if(request[1] == "random") {
        // No input
        if((int)request.size() == 2){
            // Operate request
            int n = randomGenerator.random(1, 20);
            int m = randomGenerator.random(n*2, 50);
            hashtable.random(n, m);
        }
        // With input
        else if((int)request.size() == 4) {
            int n = stoi(request[2]);
            int m = stoi(request[3]);
            cout << n << ' ' << m << '\n';
            hashtable.random(n, m);
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
    return true;
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

bool DS2::operateInsert(vector<string>& request, int stepRequest, string& explanationText) {
    bool done = true;
    int val = stoi(request[1]);
    done = animationManager.insert(val, stepRequest, explanationText);
    return done;
}

bool DS2::operateRemove(vector<string>& request, int stepRequest, string& explanationText){
    bool done = true;
    int val = stoi (request[1]);
    done = animationManager.remove(val, stepRequest, explanationText);
    return done;
}

bool DS2::operateSearch(vector<string>& request, int stepRequest, string& explanationText) {
    bool done = true;
    int val = stoi(request[1]);
    done = animationManager.search(val, stepRequest, explanationText);
    return done;
}

void DS2::randomInitialize(int n, int m) {
    hashtable.random(n,m);
}


void DS2::vectorIntInitialize(vector<int>& vi) {
    hashtable.build(vi);
}

void DS2::loadTextures(void) {
    Image image = LoadImage("Assets/Images/PFileIcon.png");
    icon = LoadTextureFromImage(image);
    UnloadImage(image);
}