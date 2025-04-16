#include "../header/PDSAnimation.h"

bool PDSAnimation::search(int value, int stepRequest, string& explanationText) {
    /*
    00. tmp = head
    01. while(tmp != nullptr) :
    02.     if(tmp->data == value): return tmp
    03.     tmp = tmp->pNext
    02. return nullptr
    */
    bool done = true;
    bool forward = stepRequest != skipBackward && stepRequest != goBackward;
    if(forward && taskManagementPointer->doneTask()) {
        return true;
    }
    int step = taskManagementPointer->getStep();
    if(stepRequest == play) 
        waitRequest = false;
    else if(stepRequest == skipBackward || stepRequest == goBackward || stepRequest == goForward || stepRequest == skipForward) 
        waitRequest = true;
    if(step == 0) {
        done = forward ? searchStep0(value, stepRequest, explanationText) : false;
    }
    else if(step == 1) {
        done = forward ? searchStep1(value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 2) {
        done = forward ? searchStep2(value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 3) {
        done = forward ? searchStep3(value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    return done;
}
bool PDSAnimation::searchStep0(int value, int stepRequest, string& explanationText) {
    cout << "searchStep0\n";;
    // 00. tmp = head
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        recordPNodePointer(&dataStructurePointer->animationTmp, false);
        dataStructurePointer->animationTmp = dataStructurePointer->head;
        recordBool(&dataStructurePointer->animationTmp->highlight);
        dataStructurePointer->animationTmp->highlight = true;
        makeVersion();
    }
    // Explanation
    explanationText = "tmp points to head.";
    // Skip
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        recordBool(&dataStructurePointer->animationTmp->highlight);
        dataStructurePointer->animationTmp->highlight = false;
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return searchStep1(value, stepRequest, explanationText);
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::searchStep1(int value, int stepRequest, string& explanationText) {
    cout << "searchStep1\n";
    // 01. while(tmp != nullptr) :
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    cout << taskManagementPointer->getTime() << '\n';
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        cout << "Begin algorithm\n";
        bool con0 = dataStructurePointer->animationTmp != nullptr;
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->takeCondition(con0);
        if(con0) {
            recordBool(&dataStructurePointer->animationTmp->highlight);
            dataStructurePointer->animationTmp->highlight = true;
        }
        makeVersion();
    }
    cout << taskManagementPointer->conditionStack.size() << '\n';
    // Explanation
    if(taskManagementPointer->getCondition(0)) {
        explanationText = "tmp is not null";
    }
    else {
        explanationText = "tmp is null";
    }
    // Skip
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        if(taskManagementPointer->getCondition(0)) {
            recordBool(&dataStructurePointer->animationTmp->highlight);
            dataStructurePointer->animationTmp->highlight = false;
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return searchStep2(value, stepRequest, explanationText);
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::searchStep2(int value, int stepRequest, string& explanationText) {
    cout << "searchStep2\n";
    /* 02.
        True:
            if(tmp->data == value): return tmp
        False:
            return nullptr
    */
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con0 = taskManagementPointer->getCondition(0);
        if(con0) {
            if(dataStructurePointer->animationTmp->data == value) {
                recordBool(&dataStructurePointer->animationTmp->highlight);
                dataStructurePointer->animationTmp->highlight = true;
            }
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition(0)) {
        if(dataStructurePointer->animationTmp->data == value)
            explanationText = "Found the node with input value!";
        else
            explanationText = "This is not the wanted node\nContinue.";
    }
    else {
        explanationText = "Couldn't find the node with input value!";
    }
    // Skip
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        if(taskManagementPointer->getCondition(0)) {
            if(dataStructurePointer->animationTmp->data == value) {
                recordBool(&dataStructurePointer->animationTmp->highlight);
                dataStructurePointer->animationTmp->highlight = false;

                recordPNodePointer(&dataStructurePointer->animationTmp, false);
                dataStructurePointer->animationTmp = nullptr;
                recordBool(&taskManagementPointer->taskDone);
                recordVectorBool(&taskManagementPointer->conditionStack);
                taskManagementPointer->popCondition();
                return true;
            }
            else {
                recordFloat(&taskManagementPointer->time);
                recordInt(&taskManagementPointer->step);
                taskManagementPointer->nextStep();
                // Skip
                if(stepRequest == skipForward) {
                    return searchStep3(value, stepRequest, explanationText);
                }
            }
        }
        else {
            recordPNodePointer(&dataStructurePointer->animationTmp, false);
            dataStructurePointer->animationTmp = nullptr;
            recordBool(&taskManagementPointer->taskDone);
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
            return true;
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::searchStep3(int value, int stepRequest, string& explanationText) {
    cout << "searchStep3\n";
    // 03. tmp = tmp->pNext
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        recordPNodePointer(&dataStructurePointer->animationTmp, false);
        dataStructurePointer->animationTmp = dataStructurePointer->animationTmp->pNext;
        if(dataStructurePointer->animationTmp != nullptr) {
            recordBool(&dataStructurePointer->animationTmp->highlight);
            dataStructurePointer->animationTmp->highlight = true;
        }
        makeVersion();
    }
    // Explanation
    explanationText = "Traverse tmp.";
    // Skip
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        if(dataStructurePointer->animationTmp != nullptr) {
            recordBool(&dataStructurePointer->animationTmp->highlight);
            dataStructurePointer->animationTmp->highlight = false;
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->popCondition();
        taskManagementPointer->step = 1;
        taskManagementPointer->time = 0.f;
        // Skip
        if(stepRequest == skipForward) {
            return searchStep1(value, stepRequest, explanationText);
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
}