#include "../header/DS2.h"
DS2::DS2(void) :
    functionArea(PConstants::PFunctionArea::pos, PConstants::PFunctionArea::size),
    stepByStepMenu(PConstants::PStepByStepMenu::pos, PConstants::PStepByStepMenu::size),
    titleBox(PConstants::PTitleBar::pos, PConstants::PTitleBar::size, PConstants::PTitleBar::outlineThickness, PConstants::PTitleBar::boxColor, PConstants::PTitleBar::outlineColor, "HASH TABLE LINEAR PROBING", PConstants::PTitleBar::textSize),
    hashtable(),
    explanationArea(),
    animationManager(),
    pseudocodeArea(),
    speedSlider(PConstants::PSlider::pos, PConstants::PSlider::size) {
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
        PConstants::PSlider::barColor = SEASHELL;
        PConstants::PSlider::thumbColor = BLACK;
        PConstants::PSlider::thumbHighlightColor = DARKGRAY;
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
        PConstants::PSlider::barColor = {73, 73, 73, 255};
        PConstants::PSlider::thumbColor = {204, 204, 204, 255};
        PConstants::PSlider::thumbHighlightColor = {204, 204, 204, 255};
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

      // Draw the pseudo-code area
      pseudocodeArea.draw();

      // Draw Data Structure
      hashtable.draw();

      // Draw Speed Slider
      speedSlider.draw();
}

void DS2::update(void){
    // Take requests from user and put it into queue, and update the function area
    if(taskManagement.takeRequest(functionArea.update())) {
        // Reset animation management
        animationManager.reset();
        if((int)taskManagement.getTask().size() == 2 && taskManagement.getTask()[1] == "update") {
            if(hashtable.chosenSquare != nullptr && hashtable.chosenSquare->visited)
                hashtable.querySquare = hashtable.chosenSquare;
            else {
                hashtable.querySquare = nullptr;
            }
        }
    }

    // Update step-by-step menu
    stepByStepMenu.update();
    int stepRequest = stepByStepMenu.getRequest();

    // Get current request
    vector<string> request = taskManagement.getTask();
    int taskType = taskManagement.getTaskType();

    // Explanation
    string explanationText;

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

    explanationArea.update(explanationText);

    // Update hash table
    hashtable.update();

    // Update speed slider
    speedSlider.update();
    PConstants::PAnimation::waitTime = 0.5f / speedSlider.getPercentage();
}

bool DS2::operateInitialize(vector<string>& request) {
    if(taskManagement.doneTask()) {
        return true;
    }
    
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
    if(request[1] == "update" && hashtable.querySquare == nullptr) return true;

    bool done = true;
    int val = request[1] == "update" ? hashtable.querySquare->value : stoi(request[1]);
    int codeLine = -1;
    done = animationManager.insert(val, stepRequest, explanationText, codeLine);
    vector<string> codes = {
        "if n == size: return", // line 0
        "key = value % mod", // line 1
        "while table[key].visited == true:", // line 2
        "    key = key + 1 % mod", // line 3
        "table[key].value = value", // line 4
        "table[key].visited = true, table[key].deleted = false", // line 5
        "n++" // line 6
    };
    pseudocodeArea.setPseudoCode(codes, 7);
    pseudocodeArea.update(codeLine);
    return done;
}

bool DS2::operateRemove(vector<string>& request, int stepRequest, string& explanationText){
    if(request[1] == "update" && hashtable.querySquare == nullptr) return true;
    bool done = true;
    int codeLine = -1;
    int val = request[1] == "update" ? hashtable.querySquare->value : stoi(request[1]);
    done = animationManager.remove(val, stepRequest, explanationText, codeLine);
    vector<string> codes = {
        "key = value % size, originalKey = key", // line 0
        "while table[key].visited || table[key].deleted :", // line 1
        "    if table[key].visited && table[key].value == value :", // line 2
        "        table[key].visited = false, table[key].deleted = true, n--, return", // line 3
        "    key = (key + 1) % size", // line 4
        "    if key == originalKey : return" // line 5
    };
    pseudocodeArea.setPseudoCode(codes, 6);
    pseudocodeArea.update(codeLine);
    return done;
}

bool DS2::operateSearch(vector<string>& request, int stepRequest, string& explanationText) {
    if(request[1] == "update" && hashtable.querySquare == nullptr) return true;
    bool done = true;
    int val = request[1] == "update" ? hashtable.querySquare->value : stoi(request[1]);
    int codeLine = -1;
    done = animationManager.search(val, stepRequest, explanationText, codeLine);
    vector<string> codes = {
        "key = value % size, originalKey = key", // line 0
        "while table[key].visited || table[key].deleted :", // line 1
        "    if table[key].visited && table[key].value == value :", // line 2
        "        return true", // line 3
        "    key = (key + 1) % size", // line 4
        "    if key == originalKey : return false" // line 5
    };
    pseudocodeArea.setPseudoCode(codes, 6);
    pseudocodeArea.update(codeLine);
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