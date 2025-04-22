#include "../header/DDSAnimation.h"
#include "../header/PConstants.h"

void DDSAnimation::reset(void) {
    // Reset the animation management
    undoStack = stack<string>();
    undoBoolStack = stack<pair<bool *, bool>>();
    undoIntStack = stack<pair<int *, int>>();
    undoFloatStack = stack<pair<float *, float>>();
    undoVectorBoolStack = stack<pair<vector<bool> *, vector<bool>>>();
    undoVectorAnimatedSquareStack = stack<pair<vector<AnimatedSquare> *, vector<AnimatedSquare>>>();
    waitRequest = false;
}
void DDSAnimation::makeVersion(void) {
    undoStack.push("Begin");
}
void DDSAnimation::recordBool(bool * p) {
    undoStack.push("bool");
    undoBoolStack.push({p, *p});
}
void DDSAnimation::recordInt(int * p) {
    undoStack.push("int");
    undoIntStack.push({p, *p});
}
void DDSAnimation::recordFloat(float * p) {
    undoStack.push("float");
    undoFloatStack.push({p, *p});
}
void DDSAnimation::recordVectorBool(vector<bool> * p) {
    undoStack.push("vector<bool>");
    undoVectorBoolStack.push({p, *p});
}
void DDSAnimation::recordVectorAnimatedSquare(vector<AnimatedSquare> * p) {
    undoStack.push("vector<AnimatedSquare>");
    undoVectorAnimatedSquareStack.push({p, *p});
}
bool DDSAnimation::undo(int stepRequest) {
    int cntBegin = 0;
    while(true) {
        if(undoStack.empty()) {
            cerr << "Error: DDSAnimation::undo().\n";
            exit(0);
        }
        string top = undoStack.top();
        if(top == "Begin")
            cntBegin++;
        if(stepRequest == goBackward && top == "Begin" && cntBegin == 2) {
            break;
        }
        else if(stepRequest == skipBackward && undoStack.size() == 1) {
            break;
        }
        undoStack.pop();
        if(top == "bool") {
            undoBool();
        }
        else if(top == "int") {
            undoInt();
        }
        else if(top == "float") {
            undoFloat();
        }
        else if(top == "vector<bool>") {
            undoVectorBool();
        }
        else if(top == "vector<AnimatedSquare>") {
            undoVectorAnimatedSquare();
        }
    }
    return false;
}
void DDSAnimation::undoBool(void) {
    if (undoBoolStack.empty()) {
        cerr << "Error: DDSAnimation::undoBool.\n";
        exit(1);
    }
    *undoBoolStack.top().first = undoBoolStack.top().second;
    undoBoolStack.pop();
}
void DDSAnimation::undoInt(void) {
    if (undoIntStack.empty()) {
        cerr << "Error: DDSAnimation::undoInt.\n";
        exit(1);
    }
    *undoIntStack.top().first = undoIntStack.top().second;
    undoIntStack.pop();
}
void DDSAnimation::undoFloat(void) {
    if (undoFloatStack.empty()) {
        cerr << "Error: DDSAnimation::undoFloat.\n";
        exit(1);
    }
    *undoFloatStack.top().first = undoFloatStack.top().second;
    undoFloatStack.pop();
}
void DDSAnimation::undoVectorBool(void) {
    if(undoVectorBoolStack.empty()) {
        cerr << "Error: DDSAnimation::undoVectorBool.\n";
        exit(1);
    }
    *undoVectorBoolStack.top().first = undoVectorBoolStack.top().second;
    undoVectorBoolStack.pop();
}
void DDSAnimation::undoVectorAnimatedSquare(void) {
    if (undoVectorAnimatedSquareStack.empty()) {
        cerr << "Error: DDSAnimation::undoVectorAnimatedSquare.\n";
        exit(1);
    }
    *undoVectorAnimatedSquareStack.top().first = undoVectorAnimatedSquareStack.top().second;
    undoVectorAnimatedSquareStack.pop();
}

bool DDSAnimation::insert(int value, int stepRequest, string& explanationText, int& codeLine) {
    /*
    00. if n == size: return
    01. key = value % mod 
    02. while (table[key].visited) :
    03.	key = (key + 1) % mod;
    03. table[key].value = value;
    04. table[key].visited = true, table[key].deleted = false
    05. n++;
    */
    bool done = false;
    bool forward = (stepRequest != goBackward) && (stepRequest != skipBackward);
    if(forward && taskManagementPointer->doneTask()) {
        return true;
    }
    if(stepRequest == play) {
        waitRequest = false;
    }
    else if(stepRequest == goBackward || stepRequest == skipBackward || stepRequest == goForward || stepRequest == skipForward) {
        waitRequest = true;
    }
    int step = taskManagementPointer->getStep();
    cout << step << ' ' << taskManagementPointer->getNumCondition() << '\n';
    // Step 0
    if(step == 0) {
        done = forward ? insertStep0(value, stepRequest, explanationText, codeLine) : false;
    }
    // Step 1
    else if(step == 1) {
        done = forward ? insertStep1(value, stepRequest, explanationText, codeLine) : undo(stepRequest);
    }
    // Step 2
    else if(step == 2) {
        done = forward ? insertStep2(value, stepRequest, explanationText, codeLine) : undo(stepRequest);
    }
    else if(step == 3) {
        done = forward ? insertStep3(value, stepRequest, explanationText, codeLine) : undo(stepRequest);
    }
    else if(step == 4) {
        done = forward ? insertStep4(value, stepRequest, explanationText, codeLine) : undo(stepRequest);
    }
    else if(step == 5) {
        done = forward ? insertStep5(value, stepRequest, explanationText, codeLine) : undo(stepRequest);
    }
    return done;
}

bool DDSAnimation::insertStep0(int value, int stepRequest, string& explanationText, int& codeLine) {
    // 00. if n == size: return
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = dataStructurePointer->n == dataStructurePointer->table.size();
        taskManagementPointer->takeCondition(condition);
        makeVersion();
    }
    // Explanation
    explanationText = "Check if the table is full.";
    codeLine = 0;
    // Skip
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if(doneStep) {
        if(taskManagementPointer->getCondition(0) == true) {
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
            return true;
        }
        else {
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
            recordFloat(&taskManagementPointer->time);
            recordInt(&taskManagementPointer->step);
            taskManagementPointer->nextStep();
        }
        // Skip
        if(stepRequest == skipForward) {
            return insertStep1(value, stepRequest, explanationText, codeLine);
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
}
bool DDSAnimation::insertStep1(int value, int stepRequest, string &explanationText, int& codeLine) {
    // 01. key = value % size
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        recordInt(&dataStructurePointer->key);
        dataStructurePointer->key = value % (int)dataStructurePointer->table.size();
        recordBool(&dataStructurePointer->table[dataStructurePointer->key].highlight);
        dataStructurePointer->table[dataStructurePointer->key].highlight = true;
        makeVersion();
    }
    // Explanation
    explanationText = "Calculate the key as value % size.";
    codeLine = 1;
    // Skip
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if(doneStep) {
        recordBool(&dataStructurePointer->table[dataStructurePointer->key].highlight);
        dataStructurePointer->table[dataStructurePointer->key].highlight = false;
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        if(stepRequest == skipForward) {
            return insertStep2(value, stepRequest, explanationText, codeLine);
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
}
bool DDSAnimation::insertStep2(int value, int stepRequest, string &explanationText, int& codeLine) {
    // 02. while (table[key].visited) :
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con0 = dataStructurePointer->table[dataStructurePointer->key].visited;
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->takeCondition(con0);
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition(0)) {
        explanationText = "Visited.\nContinue the loop.";
    }
    else {
        explanationText = "Unvisited.\nExit the loop.";
    }
    codeLine = 2;
    // Skip
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if(doneStep) {
        if(taskManagementPointer->getCondition(0) == false) {
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        if(stepRequest == skipForward) {
            return insertStep3(value, stepRequest, explanationText, codeLine);
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
}
bool DDSAnimation::insertStep3(int value, int stepRequest, string &explanationText, int& codeLine) {
    /* 03.
    condition.size() == 1 :
        key = (key + 1) % mod;
    condition.size() == 0 :
        table[key].value = value;
    */
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        if(taskManagementPointer->getNumCondition() == 1) {
            recordInt(&dataStructurePointer->key);
            dataStructurePointer->key = (dataStructurePointer->key + 1) % dataStructurePointer->table.size();
            recordBool(&dataStructurePointer->table[dataStructurePointer->key].highlight);
            dataStructurePointer->table[dataStructurePointer->key].highlight = true;
        }
        else {
            recordVectorAnimatedSquare(&dataStructurePointer->table);
            dataStructurePointer->table[dataStructurePointer->key].value = value;
            recordBool(&dataStructurePointer->table[dataStructurePointer->key].highlight);
            dataStructurePointer->table[dataStructurePointer->key].highlight = true;
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getNumCondition() == 1) {
        explanationText = "Traverse the key.";
        codeLine = 3;
    }
    else {
        explanationText = "Update the cell.";
        codeLine = 4;
    }
    // Skip
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if(doneStep) {
        if(taskManagementPointer->getNumCondition() == 1) {
            recordBool(&dataStructurePointer->table[dataStructurePointer->key].highlight);
            dataStructurePointer->table[dataStructurePointer->key].highlight = false;
            recordFloat(&taskManagementPointer->time);
            recordInt(&taskManagementPointer->step);
            recordBool(&taskManagementPointer->taskDone);
            taskManagementPointer->prevStep();
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
            if(stepRequest == skipForward) {
                return insertStep2(value, stepRequest, explanationText, codeLine);
            }
        }
        else {
            recordBool(&dataStructurePointer->table[dataStructurePointer->key].highlight);
            dataStructurePointer->table[dataStructurePointer->key].highlight = false;
            recordFloat(&taskManagementPointer->time);
            recordInt(&taskManagementPointer->step);
            taskManagementPointer->nextStep();
            if(stepRequest == skipForward) {
                return insertStep4(value, stepRequest, explanationText, codeLine);
            }
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
}
bool DDSAnimation::insertStep4(int value, int stepRequest, string &explanationText, int& codeLine) {
    // 04. table[key].visited = true, table[key].deleted = false;
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if (taskManagementPointer->getTime() == 0.f) {
        recordBool(&dataStructurePointer->table[dataStructurePointer->key].visited);
        recordBool(&dataStructurePointer->table[dataStructurePointer->key].deleted);
        dataStructurePointer->table[dataStructurePointer->key].visited = true;
        dataStructurePointer->table[dataStructurePointer->key].deleted = false;
        makeVersion();
    }
    // Explanation
    explanationText = "Mark the current key as visited.";
    codeLine = 5;
    // Skip
    if (stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if (doneStep) {
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        if (stepRequest == skipForward) {
            return insertStep5(value, stepRequest, explanationText, codeLine);
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
}
bool DDSAnimation::insertStep5(int value, int stepRequest, string &explanationText, int& codeLine) {
    // 05. n++;
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if (taskManagementPointer->getTime() == 0.f) {
        recordInt(&dataStructurePointer->n);
        dataStructurePointer->n++;
        makeVersion();
    }
    // Explanation
    explanationText = "Increment the number of elements.";
    codeLine = 6;
    // Skip
    if (stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if (doneStep) {
        recordInt(&dataStructurePointer->key);
        recordInt(&dataStructurePointer->originalKey);
        dataStructurePointer->key = dataStructurePointer->originalKey = -1;
        recordBool(&taskManagementPointer->taskDone);
        return true;
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
}

  // Remove animation
bool DDSAnimation::remove(int value, int stepRequest, string& explanationText, int& codeLine){
    /*
    00. key = value % size, originalKey = key
    01. while (table[key].visited || table[key].deleted):
    02.	if(table[key].visited && table[key].value == value) :
    03.		table[key].visited = false, table[key].deleted = true; n--; return;
    03.	key = (key+1) % size;
    04.	if (key == originalKey) return;
    */
    bool done = false;
    bool forward = (stepRequest != goBackward) && (stepRequest != skipBackward);
    if(forward && taskManagementPointer->doneTask()) {
        return true;
    }
    if(stepRequest == play) {
        waitRequest = false;
    }
    else if(stepRequest == goBackward || stepRequest == skipBackward || stepRequest == goForward || stepRequest == skipForward) {
        waitRequest = true;
    }
    int step = taskManagementPointer->getStep();
    cout << step << ' ' << taskManagementPointer->getNumCondition() << '\n';
    // Step 0
    if(step == 0) {
        done = forward ? removeStep0(value, stepRequest, explanationText, codeLine) : false;
    }
    // Step 1
    else if(step == 1) {
        done = forward ? removeStep1(value, stepRequest, explanationText, codeLine) : undo(stepRequest);
    }
    // Step 2
    else if(step == 2) {
        done = forward ? removeStep2(value, stepRequest, explanationText, codeLine) : undo(stepRequest);
    }
    // Step 3
    else if(step == 3) {
        done = forward ? removeStep3(value, stepRequest, explanationText, codeLine) : undo(stepRequest);
    }
    // Step 4
    else if(step == 4) {
        done = forward ? removeStep4(value, stepRequest, explanationText, codeLine) : undo(stepRequest);
    }
    return done;
}
bool DDSAnimation::removeStep0(int value, int stepRequest, string& explanationText, int& codeLine){
    // 00. key = value % size, originalKey = key
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        dataStructurePointer->key = value % (int)dataStructurePointer->table.size();
        dataStructurePointer->table[dataStructurePointer->key].highlight = true;
        dataStructurePointer->originalKey = dataStructurePointer->key;
        makeVersion();
    }
    // Explanation
    explanationText = "Calculate the key as value % size.";
    codeLine = 0;
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if(doneStep) {
        recordBool(&dataStructurePointer->table[dataStructurePointer->key].highlight);
        dataStructurePointer->table[dataStructurePointer->key].highlight = false;
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return removeStep1(value, stepRequest, explanationText, codeLine);
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
} // Step 0
bool DDSAnimation::removeStep1(int value, int stepRequest, string& explanationText, int& codeLine){
    // 01. while (table[key].visited || table[key].deleted):
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con0 = dataStructurePointer->table[dataStructurePointer->key].visited || dataStructurePointer->table[dataStructurePointer->key].deleted;
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->takeCondition(con0);
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition(0)) {
        explanationText = "Visited or deleted.\nContinue the loop.";
    }
    else {
        explanationText = "Unvisited and not deleted.\nExit the loop.";
    }
    codeLine = 1;
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if(doneStep) {
        if(taskManagementPointer->getCondition(0) == false) {
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
            recordBool(&taskManagementPointer->taskDone);
            return true;
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return removeStep2(value, stepRequest, explanationText, codeLine);
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
} // Step 1
bool DDSAnimation::removeStep2(int value, int stepRequest, string& explanationText, int& codeLine){
    // 02.	if(table[key].visited && table[key].value == value) :
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con1 = dataStructurePointer->table[dataStructurePointer->key].visited && dataStructurePointer->table[dataStructurePointer->key].value == value;
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->takeCondition(con1);
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition(1)) {
        explanationText = "Found the wanted cell.";
    }
    else {
        explanationText = "Not the wanted cell.";
    }
    codeLine = 2;
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if(doneStep) {
        if(taskManagementPointer->getCondition(1) == false) {
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return removeStep3(value, stepRequest, explanationText, codeLine);
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
} // Step 2   
bool DDSAnimation::removeStep3(int value, int stepRequest, string& explanationText, int& codeLine){
    /* 03.
    condition.size() == 2 :
        table[key].visited = false, table[key].deleted = true; n--; return;
    condition.size() == 1 :
        key = (key + 1) % size;
    */
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        if (taskManagementPointer->getNumCondition() == 2) {
            recordBool(&dataStructurePointer->table[dataStructurePointer->key].visited);
            recordBool(&dataStructurePointer->table[dataStructurePointer->key].deleted);
            dataStructurePointer->table[dataStructurePointer->key].visited = false;
            dataStructurePointer->table[dataStructurePointer->key].deleted = true;
            recordInt(&dataStructurePointer->n);
            dataStructurePointer->n--;
        }
        else {
            recordInt(&dataStructurePointer->key);
            dataStructurePointer->key = (dataStructurePointer->key + 1) % dataStructurePointer->table.size();
            recordBool(&dataStructurePointer->table[dataStructurePointer->key].highlight);
            dataStructurePointer->table[dataStructurePointer->key].highlight = true;
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getNumCondition() == 2) {
        explanationText = "Found the wanted cell.\nMark it as unvisited and deleted.";
        codeLine = 3;
    }
    else {
        explanationText = "Traverse the key.";
        codeLine = 4;
    }
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if(doneStep) {
        if (taskManagementPointer->getNumCondition() == 2) {
            recordVectorBool(&taskManagementPointer->conditionStack);
            for(int i = 0; i < 2; i++) taskManagementPointer->popCondition();
            cout << taskManagementPointer->getNumCondition() << '\n';
            recordBool(&taskManagementPointer->taskDone);
            return true;
        }
        else {
            recordBool(&dataStructurePointer->table[dataStructurePointer->key].highlight);
            dataStructurePointer->table[dataStructurePointer->key].highlight = false;
            recordFloat(&taskManagementPointer->time);
            recordInt(&taskManagementPointer->step);
            taskManagementPointer->nextStep();
            // Skip
            if(stepRequest == skipForward) {
                return removeStep4(value, stepRequest, explanationText, codeLine);
            }
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
} // Step 3
bool DDSAnimation::removeStep4(int value, int stepRequest, string& explanationText, int& codeLine){
    // 04. if (key == originalKey) return;
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con1 = dataStructurePointer->key == dataStructurePointer->originalKey;
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->takeCondition(con1);
        makeVersion();
    }
    // Explanation    
    explanationText = "Check if the current key is the original key again.";
    codeLine = 5;
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if(doneStep) {
        if(taskManagementPointer->getCondition(1) == true) {
            recordVectorBool(&taskManagementPointer->conditionStack);
            for (int i=0; i<2; i++) taskManagementPointer->popCondition();
            recordBool(&taskManagementPointer->taskDone);
            return true;
        }
        else {
            recordVectorBool(&taskManagementPointer->conditionStack);
            for(int i = 0; i < 2; i++) taskManagementPointer->popCondition();
            recordFloat(&taskManagementPointer->time);
            recordInt(&taskManagementPointer->step);
            recordBool(&taskManagementPointer->taskDone);
            for(int i = 0; i < 3; i++) taskManagementPointer->prevStep();
            if(stepRequest == skipForward) {
                return removeStep1(value, stepRequest, explanationText, codeLine);
            }
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
} // Step 4

// Search animation
bool DDSAnimation::search(int value, int stepRequest, string& explanationText, int& codeLine) {
    /*
    00. key = value % size, originalKey = key
    01. while (table[key].visited || table[key].deleted):
    02.	if(table[key].visited && table[key].value == value) :
    03.		return true;
    03.	key = (key+1) % size;
    04.	if (key == originalKey) return false;
    */
    bool done = false;
    bool forward = (stepRequest != goBackward) && (stepRequest != skipBackward);
    if(forward && taskManagementPointer->doneTask()) {
        return true;
    }
    if(stepRequest == play) {
        waitRequest = false;
    }
    else if(stepRequest == goBackward || stepRequest == skipBackward || stepRequest == goForward || stepRequest == skipForward) {
        waitRequest = true;
    }
    int step = taskManagementPointer->getStep();
    cout << step << ' ' << taskManagementPointer->getNumCondition() << '\n';
    // Step 0
    if(step == 0) {
        done = forward ? searchStep0(value, stepRequest, explanationText, codeLine) : false;
    }
    // Step 1
    else if(step == 1) {
        done = forward ? searchStep1(value, stepRequest, explanationText, codeLine) : undo(stepRequest);
    }
    // Step 2
    else if(step == 2) {
        done = forward ? searchStep2(value, stepRequest, explanationText, codeLine) : undo(stepRequest);
    }
    // Step 3
    else if(step == 3) {
        done = forward ? searchStep3(value, stepRequest, explanationText, codeLine) : undo(stepRequest);
    }
    // Step 4
    else if(step == 4) {
        done = forward ? searchStep4(value, stepRequest, explanationText, codeLine) : undo(stepRequest);
    }
    return done;
}

bool DDSAnimation::searchStep0(int value, int stepRequest, string& explanationText, int& codeLine) {
    // 00. key = value % size, originalKey = key
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        recordInt(&dataStructurePointer->key);
        dataStructurePointer->key = value % (int)dataStructurePointer->table.size();
        recordBool(&dataStructurePointer->table[dataStructurePointer->key].highlight);
        dataStructurePointer->table[dataStructurePointer->key].highlight = true;
        recordInt(&dataStructurePointer->originalKey);
        dataStructurePointer->originalKey = dataStructurePointer->key;
        makeVersion();
    }
    // Explanation
    explanationText = "Calculate the key as value % size.";
    codeLine = 0;
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if(doneStep) {
        recordBool(&dataStructurePointer->table[dataStructurePointer->key].highlight);
        dataStructurePointer->table[dataStructurePointer->key].highlight = false;
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return searchStep1(value, stepRequest, explanationText, codeLine);
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
} // Step 0
bool DDSAnimation::searchStep1(int value, int stepRequest, string& explanationText, int& codeLine) {
    // 01. while (table[key].visited || table[key].deleted):
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con0 = dataStructurePointer->table[dataStructurePointer->key].visited || dataStructurePointer->table[dataStructurePointer->key].deleted;
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->takeCondition(con0);
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition(0)) {
        explanationText = "Visited or deleted.\nContinue the loop.";
    }
    else {
        explanationText = "Unvisited and not deleted.\nExit the loop.";
    }
    codeLine = 1;
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if(doneStep) {
        if(taskManagementPointer->getCondition(0) == false) {
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
            recordBool(&taskManagementPointer->taskDone);
            return true;
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return searchStep2(value, stepRequest, explanationText, codeLine);
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
} // Step 1
bool DDSAnimation::searchStep2(int value, int stepRequest, string& explanationText, int& codeLine) {
    // 02.	if(table[key].visited && table[key].value == value) :
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con1 = dataStructurePointer->table[dataStructurePointer->key].visited && dataStructurePointer->table[dataStructurePointer->key].value == value;
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->takeCondition(con1);
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition(1)) {
        explanationText = "Found the wanted cell.";
    }
    else {
        explanationText = "Not the wanted cell.";
    }
    codeLine = 2;
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if(doneStep) {
        if(taskManagementPointer->getCondition(1) == false) {
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return searchStep3(value, stepRequest, explanationText, codeLine);
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
} // Step 2
bool DDSAnimation::searchStep3(int value, int stepRequest, string& explanationText, int& codeLine) {
    /* 03.
    condition.size() == 2 :
        return true;
    condition.size() == 1 :
        key = (key + 1) % size;
    */
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        if (taskManagementPointer->getNumCondition() == 2) {
            recordBool(&dataStructurePointer-> table[dataStructurePointer->key].highlightSearch);
            dataStructurePointer->table[dataStructurePointer->key].highlightSearch = true;
            // recordVectorBool(&taskManagementPointer->conditionStack);
            // for(int i = 0; i < 2; i++) taskManagementPointer->popCondition();
            // recordBool(&taskManagementPointer->taskDone);
            // return true;
        }
        else {
            recordInt(&dataStructurePointer->key);
            dataStructurePointer->key = (dataStructurePointer->key + 1) % dataStructurePointer->table.size();
            recordBool(&dataStructurePointer->table[dataStructurePointer->key].highlight);
            dataStructurePointer->table[dataStructurePointer->key].highlight = true;
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getNumCondition() == 2) {
        explanationText = "Found the wanted value.\nReturn true.";
        codeLine = 3;
    }
    else {
        explanationText = "Traverse the key.";
        codeLine = 4;
    }
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if(doneStep) {
        if (taskManagementPointer->getNumCondition() == 2) {
            recordBool(&dataStructurePointer->table[dataStructurePointer->key].highlightSearch);
            dataStructurePointer->table[dataStructurePointer->key].highlightSearch = false;
            recordVectorBool(&taskManagementPointer->conditionStack);
            for (int i=0; i<2; i++) taskManagementPointer->popCondition();
            recordBool(&taskManagementPointer->taskDone);
            return true;
        }
        else {
            recordBool(&dataStructurePointer->table[dataStructurePointer->key].highlight);
            dataStructurePointer->table[dataStructurePointer->key].highlight = false;
            recordFloat(&taskManagementPointer->time);
            recordInt(&taskManagementPointer->step);
            taskManagementPointer->nextStep();
            // Skip
            if(stepRequest == skipForward) {
                return searchStep4(value, stepRequest, explanationText, codeLine);
            }
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
} // Step 3
bool DDSAnimation::searchStep4(int value, int stepRequest, string& explanationText, int& codeLine) {
    // 04. if (key == originalKey) return false;
    bool doneStep = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con1 = dataStructurePointer->key == dataStructurePointer->originalKey;
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->takeCondition(con1);
        makeVersion();
    }
    // Explanation
    explanationText = "Check if the current key is the original key again.";
    codeLine = 5;
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneStep = true;
    }
    // End algorithm
    if(doneStep) {
        if(taskManagementPointer->getCondition(1) == true) {
            recordVectorBool(&taskManagementPointer->conditionStack);
            for (int i=0; i<2; i++) taskManagementPointer->popCondition();
            recordBool(&taskManagementPointer->taskDone);
            return true;
        }
        else {
            recordVectorBool(&taskManagementPointer->conditionStack);
            for(int i = 0; i < 2; i++) taskManagementPointer->popCondition();
            recordFloat(&taskManagementPointer->time);
            recordInt(&taskManagementPointer->step);
            recordBool(&taskManagementPointer->taskDone);
            for(int i = 0; i < 3; i++) taskManagementPointer->prevStep();
            if(stepRequest == skipForward) {
                return searchStep1(value, stepRequest, explanationText, codeLine);
            }
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
} // Step 4
