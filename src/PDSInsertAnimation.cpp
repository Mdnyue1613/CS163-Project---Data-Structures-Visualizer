#include "../header/PDSAnimation.h"

bool PDSAnimation::insertHead(int value, int stepRequest, string& explanationText) {
    /*
    Pseudo code:
    Step 0.    CreateNodeBefore(0, x) : tmp = new Node(x); this node is created before the 0-th node
    Step 1.    CheckEmptyList : if(head == nullptr) : Check if the current list is empty
    The list is empty : (true)
        Step 2.  AssignTmpToHead : head = tmp
        Step 3.  AssignTmpToEnd : end = tmp
    The list is not empty : (false)
        Step 2.  AssignTmpToHeadPrev : head->pPrev = tmp
        Step 3.  AssignHeadToTmpNext : tmp->pNext = head
        Step 4.  AssignTmpToHead : head = tmp
    */
    // Track if the progress is done
    bool done = false;
    // Direction of the flow
    bool forward = (stepRequest != goBackward && stepRequest != skipBackward);
    if(forward && taskManagementPointer->doneTask())
        return true;
    // Update waitRequest state
    if(stepRequest == play)
        waitRequest = false;
    else if(stepRequest == skipBackward || stepRequest == goBackward || stepRequest == goForward || stepRequest == skipForward)
        waitRequest = true;
    // Doing steps
    int step = taskManagementPointer->getStep();
    if(step == 0) {
        done = forward ? insertHeadStep0(value, stepRequest, explanationText) : false;
    }
    else if(step == 1)
        done = forward ? insertHeadStep1(value, stepRequest, explanationText) : undoInsertHead0(value, stepRequest, explanationText);
    else if(step == 2)
        done = forward ? insertHeadStep2(value, stepRequest, explanationText) : undoInsertHead1(value, stepRequest, explanationText);
    else if(step == 3)
        done = forward ? insertHeadStep3(value, stepRequest, explanationText) : undoInsertHead2(value, stepRequest, explanationText);
    else if(step == 4)
        done = forward ? insertHeadStep4(value, stepRequest, explanationText) : undoInsertHead3(value, stepRequest, explanationText);
    else {
        cerr << "Input wrong step in DS1::insertHead(value, step)\n";
        exit(1);
    }
    if(done) {
        PNode* tmp = dataStructurePointer->head;
        while(tmp != nullptr) {
            recordVector2(&tmp->center);
            tmp = tmp->pNext;
        }
        dataStructurePointer->reloadPositions();
    }
    // Check if the progress is done
    return done;
}
bool PDSAnimation::insertHeadStep0(int value, int stepRequest, string& explanationText) {
    bool doneAnimation0 = (waitRequest == false && dataStructurePointer->createdAnimationTmp() && dataStructurePointer->animationTmpIsUpdated());
    // Begin algorithm
    if(dataStructurePointer->createdAnimationTmp() == false) {
        dataStructurePointer->createNodeBefore(0, value);
        dataStructurePointer->setHighlightAnimationTmp(true);
    }
    // Explanation text
    explanationText = "Create a new node.";
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        dataStructurePointer->quickUpdateAnimation();
        doneAnimation0 = true;
    }
    // End algorithm
    if(doneAnimation0) {
        dataStructurePointer->setHighlightAnimationTmp(false);
        taskManagementPointer->nextStep();
        // Move to the next step
        if(stepRequest == skipForward)
            return insertHeadStep1(value, stepRequest, explanationText);
    }
    return false;
}
bool PDSAnimation::insertHeadStep1(int value, int stepRequest, string& explanationText) {
    bool doneAnimation1 = (waitRequest == false && taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getNumCondition() == 0) {
        bool emptyList = dataStructurePointer->createdHead() == false;
        taskManagementPointer->takeCondition(emptyList);
        if(dataStructurePointer->createdHead())
            dataStructurePointer->setHighlightHead(true);
    }
    // Explanation text
    explanationText = "Check if the list is empty.";
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneAnimation1 = true;
    }
    // Update time
    taskManagementPointer->updateTime();
    // Go to the next step
    if(doneAnimation1) {
        if(dataStructurePointer->createdHead())
            dataStructurePointer->setHighlightHead(false);
        taskManagementPointer->nextStep();
        if(stepRequest == skipForward)
            return insertHeadStep2(value, stepRequest, explanationText);
    }
    return false;
}
bool PDSAnimation::insertHeadStep2(int value, int stepRequest, string& explanationText) {
    bool doneAnimation2 = (waitRequest == false && taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime);
    // State of the list
    bool emptyList = taskManagementPointer->getCondition();
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        if(emptyList == true) {
            dataStructurePointer->assignAnimationTmpToHead();
            dataStructurePointer->setHighlightHead(true);
        }
        else {
            dataStructurePointer->assignAnimationTmpToHeadPrev();
            dataStructurePointer->setHighlightHeadPrevLink(true);
        }
    }
    // Explanation text
    if(emptyList) {
        explanationText = "head points to tmp.";
    }
    else {
        explanationText = "head->pPrev points to tmp.";
    }
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneAnimation2 = true;
    }
    // Update time
    taskManagementPointer->updateTime();
    // Go to the next step
    if(doneAnimation2) {
        if(emptyList == true)
            dataStructurePointer->setHighlightHead(false);
        else
            dataStructurePointer->setHighlightHeadPrevLink(false);
        taskManagementPointer->nextStep();
        if(stepRequest == skipForward)
            return insertHeadStep3(value, stepRequest, explanationText);
    }
    return false;
}
bool PDSAnimation::insertHeadStep3(int value, int stepRequest, string& explanationText) {
    bool doneAnimation3 = (waitRequest == false && taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime);
    bool emptyList = taskManagementPointer->getCondition();
    // Begin lgorithm
    if(taskManagementPointer->getTime() == 0.f) {
        if(emptyList == true) {
            dataStructurePointer->assignAnimationTmpToTail();
            dataStructurePointer->setHighlightTail(true);
        }
        else {
            dataStructurePointer->assignHeadToAnimationTmpNext();
            dataStructurePointer->setHighlightAnimationTmpNextLink(true);
        }
    }
    // Explanation text
    if(emptyList) {
        explanationText = "tail points to tmp";
    }
    else {
        explanationText = "tmp->pNext points to head";
    }
    // Update time
    taskManagementPointer->updateTime();
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneAnimation3 = true;
    }
    // End algorithm
    if(doneAnimation3 == true) {
        if(emptyList == true) {
            dataStructurePointer->setHighlightTail(false);
            dataStructurePointer->setAnimationTmpToNull();
            dataStructurePointer->addNumNode(1);
            taskManagementPointer->popCondition();
            taskManagementPointer->undoCondtionStack.push_back(emptyList == true);
            return true;
        }
        else {
            dataStructurePointer->setHighlightAnimationTmpNextLink(false);
            taskManagementPointer->nextStep();
        }
        // Case skip
        if(stepRequest == skipForward) 
            return insertHeadStep4(value, stepRequest, explanationText);
    }
    return false;
}
bool PDSAnimation::insertHeadStep4(int value, int stepRequest, string& explanationText) {
    bool doneAnimation4 = (waitRequest == false && taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        dataStructurePointer->assignAnimationTmpToHead();
        dataStructurePointer->setHighlightHead(true);
    }
    // Explanation text
    explanationText = "head points to tmp.";
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        doneAnimation4 = true;
    }
    // Update time
    taskManagementPointer->updateTime();
    // End algorithm
    if(doneAnimation4) {
        dataStructurePointer->setHighlightHead(false);
        dataStructurePointer->setAnimationTmpToNull();
        dataStructurePointer->addNumNode(1);
        taskManagementPointer->undoCondtionStack.push_back(taskManagementPointer->getCondition());
        taskManagementPointer->popCondition();
        return true;
    }
    return false;
}
bool PDSAnimation::undoInsertHead0(int value, int stepRequest, string& explanationText) {
    if(dataStructurePointer->createdHead()) 
        dataStructurePointer->setHighlightHead(false);
    taskManagementPointer->popCondition();
    taskManagementPointer->prevStep();
    dataStructurePointer->setHighlightAnimationTmp(true);
    return false;
}
bool PDSAnimation::undoInsertHead1(int value, int stepRequest, string& explanationText) {
    bool condition = taskManagementPointer->getCondition();
    if(condition == true) {
        dataStructurePointer->setHighlightHead(false);
        dataStructurePointer->setHeadToNull();
    }
    else {
        dataStructurePointer->setHighlightHeadPrevLink(false);
        dataStructurePointer->setHeadPrevLinkToNull();
    }
    taskManagementPointer->prevStep();
    if(dataStructurePointer->createdHead())
        dataStructurePointer->setHighlightHead(true);
    if(stepRequest == skipBackward)
        return undoInsertHead0(value, stepRequest, explanationText);
    return false;
}
bool PDSAnimation::undoInsertHead2(int value, int stepRequest, string& explanationText) {
    if(taskManagementPointer->doneTask()) {
        taskManagementPointer->takeCondition(taskManagementPointer->undoCondtionStack.back());
        taskManagementPointer->undoCondtionStack.pop_back();
        dataStructurePointer->addNumNode(-1);
        dataStructurePointer->animationTmp = dataStructurePointer->tail;
        dataStructurePointer->setHighlightTail(true);
    }
    bool condition = taskManagementPointer->getCondition();
    if(condition == true) {
        dataStructurePointer->setHighlightTail(false);
        dataStructurePointer->setTailToNull();
    }
    else {
        dataStructurePointer->setHighlightAnimationTmpNextLink(false);
        dataStructurePointer->setAnimationTmpNextLinkToNull();
    }
    taskManagementPointer->prevStep();
    if(condition == true)
        dataStructurePointer->setHighlightHead(true);
    else
        dataStructurePointer->setHighlightHeadPrevLink(true);
    if(stepRequest == skipBackward)
        return undoInsertHead1(value, stepRequest, explanationText);
    return false;
}
bool PDSAnimation::undoInsertHead3(int value, int stepRequest, string& explanationText) {
    if(taskManagementPointer->doneTask()) {
        taskManagementPointer->takeCondition(taskManagementPointer->undoCondtionStack.back());
        taskManagementPointer->undoCondtionStack.pop_back();
        dataStructurePointer->addNumNode(-1);
        dataStructurePointer->animationTmp = dataStructurePointer->head;
        dataStructurePointer->setHighlightHead(true);
    }
    dataStructurePointer->setHighlightHead(false);
    dataStructurePointer->head = dataStructurePointer->animationTmp->pNext;
    taskManagementPointer->prevStep();
    dataStructurePointer->setHighlightAnimationTmpNextLink(true);
    if(stepRequest == skipBackward)
        return undoInsertHead2(value, stepRequest, explanationText);
    return false;
}

bool PDSAnimation::insertTail(int value, int stepRequest, string& explanationText) {
    /*
    Pseudo code:
    Step 0.    CreateNodeAfter(0, x) : tmp = new Node(x); this node is created after the 0-th node
    Step 1.    CheckEmptyList : if(head == nullptr) : Check if the current list is empty
    The list is empty : (true)
        Step 2.  AssignAnimationTmpToHead : head = tmp
        Step 3.  AssignAnimationTmpToEnd : end = tmp
    The list is not empty : (false)
        Step 2.  AssignAnimationTmpToTailNext : tail->pNext = tmp
        Step 3.  AssignTailToAnimationTmpPrev : tmp->pPrev = tail
        Step 4.  AssignAnimationTmpToTail : tail = tmp
    */
    bool done = false;
    bool forward = stepRequest != goBackward && stepRequest != skipBackward;
    if(stepRequest == play)
        waitRequest = false;
    else if(stepRequest == skipBackward || stepRequest == goBackward || stepRequest == goForward || stepRequest == skipForward)
        waitRequest = true;
    if(taskManagementPointer->doneTask() && forward)
        return true;
    int step = taskManagementPointer->getStep();
    // Step 0
    if(step == 0) {
        done = forward ? insertTailStep0(value, stepRequest, explanationText) : false;
    }
    // Step 1
    else if(step == 1) {
        done = forward ? insertTailStep1(value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    // Step 2
    else if(step == 2) {
        done = forward ? insertTailStep2(value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    // Step 3
    else if(step == 3) {
        done = forward ? insertTailStep3(value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    // Step 4
    else if(step == 4) {
        done = forward ? insertTailStep4(value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else {
        cerr << "Input wrong step in DS1::insertTail(value, step)\n";
        exit(0);
    }
    if(done) {
        PNode* tmp = dataStructurePointer->head;
        while(tmp != nullptr) {
            recordVector2(&tmp->center);
            tmp = tmp->pNext;
        }
        dataStructurePointer->reloadPositions();
    }
    // Check if the progress is done
    return done;
}
bool PDSAnimation::insertTailStep0(int value, int stepRequest, string& explanationText) {
    // 0. tmp = new Node(x);
    bool done = (waitRequest == false && dataStructurePointer->createdAnimationTmp() && dataStructurePointer->animationTmpIsUpdated());
    // Begin algorithm
    if(dataStructurePointer->createdAnimationTmp() == false) {
        dataStructurePointer->createNodeAfter(dataStructurePointer->getNumNode() - 1, value);
        dataStructurePointer->setHighlightAnimationTmp(true);
        makeVersion();
    }
    // Explanation
    explanationText = "Create a new node.";
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        recordBool(&dataStructurePointer->animationTmp->highlight);
        dataStructurePointer->setHighlightAnimationTmp(false);
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return insertTailStep1(value, stepRequest, explanationText);
        }
    }
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertTailStep1(int value, int stepRequest, string& explanationText) {
    // 1. if(head == nullptr)
    bool done = (waitRequest == false && taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = dataStructurePointer->head == nullptr;
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->takeCondition(condition);
        if(condition == false) {
            recordBool(&dataStructurePointer->head->highlight);
            dataStructurePointer->setHighlightHead(true);
        }
        makeVersion();
    }
    // Explanation
    explanationText = "Check if the list is empty.";
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        if(taskManagementPointer->getCondition() == false) {
            recordBool(&dataStructurePointer->head->highlight);
            dataStructurePointer->setHighlightHead(false);
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return insertTailStep2(value, stepRequest, explanationText);
        }
    }
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertTailStep2(int value, int stepRequest, string& explanationText) {
    // true : 2. head = tmp; false : 2. tail->pNext = tmp;
    bool done = (waitRequest == false && taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = taskManagementPointer->getCondition();
        if(condition) {
            recordPNodePointer(&dataStructurePointer->head, false);
            dataStructurePointer->assignAnimationTmpToHead();
            recordBool(&dataStructurePointer->head->highlight);
            dataStructurePointer->setHighlightHead(true);
        }
        else {
            recordPNodePointer(&dataStructurePointer->tail->pNext, false);
            dataStructurePointer->assignAnimationTmpToTailNext();
            recordBool(&dataStructurePointer->tail->lNext.highlight);
            dataStructurePointer->setHighlightTailNextLink(true);
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition()) {
        explanationText = "head points to tmp.";
    }
    else {
        explanationText = "tail->pNext points to tmp.";
    }
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        if(taskManagementPointer->getCondition()) {
            recordBool(&dataStructurePointer->head->highlight);
            dataStructurePointer->setHighlightHead(false);
        }
        else {
            recordBool(&dataStructurePointer->tail->lNext.highlight);
            dataStructurePointer->setHighlightTailNextLink(false);
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return insertTailStep3(value, stepRequest, explanationText);
        }
    }
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertTailStep3(int value, int stepRequest, string& explanationText) {
    // true : 3. tail = tmp; false : 3. tmp->pPrev = tail;
    bool done = (waitRequest == false && taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = taskManagementPointer->getCondition();
        if(condition) {
            recordPNodePointer(&dataStructurePointer->tail, false);
            dataStructurePointer->assignAnimationTmpToTail();
            recordBool(&dataStructurePointer->tail->highlight);
            dataStructurePointer->setHighlightTail(true);
        }
        else {
            recordPNodePointer(&dataStructurePointer->animationTmp->pPrev, false);
            dataStructurePointer->assignTailToAnimationTmpPrev();
            recordBool(&dataStructurePointer->animationTmp->lPrev.highlight);
            dataStructurePointer->setHighlightAnimationTmpPrevLink(true);
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition()) {
        explanationText = "tail points to tmp.";
    }
    else {
        explanationText = "tmp->pPrev points to tail.";
    }
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        if(taskManagementPointer->getCondition()) {
            recordBool(&dataStructurePointer->tail->highlight);
            dataStructurePointer->setHighlightTail(false);
            recordInt(&dataStructurePointer->n);
            dataStructurePointer->n++;
            recordPNodePointer(&dataStructurePointer->animationTmp, false);
            dataStructurePointer->animationTmp = nullptr;
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
            recordBool(&taskManagementPointer->taskDone);
            return true;
        }
        else {
            recordBool(&dataStructurePointer->animationTmp->lPrev.highlight);
            dataStructurePointer->setHighlightAnimationTmpPrevLink(false);
            recordFloat(&taskManagementPointer->time);
            recordInt(&taskManagementPointer->step);
            taskManagementPointer->nextStep();
        }
        // Skip
        if(stepRequest == skipForward) {
            return insertTailStep4(value, stepRequest, explanationText);
        }
    }
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertTailStep4(int value, int stepRequest, string& explanationText) {
    // 4. tail = tmp;
    bool done = (waitRequest == false && taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        recordPNodePointer(&dataStructurePointer->tail, false);
        dataStructurePointer->tail = dataStructurePointer->animationTmp;
        recordBool(&dataStructurePointer->tail->highlight);
        dataStructurePointer->tail->highlight = true;
        makeVersion();
    }
    // Explanation
    explanationText = "tail points to tmp.";
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        recordBool(&dataStructurePointer->tail->highlight);
        dataStructurePointer->tail->highlight = false;
        recordInt(&dataStructurePointer->n);
        dataStructurePointer->n++;
        recordPNodePointer(&dataStructurePointer->animationTmp, false);
        dataStructurePointer->animationTmp = nullptr;
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->popCondition();
        recordBool(&taskManagementPointer->taskDone);
        return true;
    }
    else taskManagementPointer->updateTime();
    return false;
}

bool PDSAnimation::insertAfter(int position, int value, int stepRequest, string& explanationText) {
    /*
    Code:
    00. Node* prev = head;
    01. for(int i = 0; i < position && prev != nullptr; i++)
    02.     prev = prev->pNext;
    03. if(prev != nullptr):
    04.     Node* tmp = new Node(x);
    05.     tmp->pNext = prev->pNext;
    06.     prev->pNext = tmp;
    07.     tmp->pPrev = prev;
    08.     if(tmp->pNext != nullptr) 
    09.         tmp->pNext->pPrev = tmp;
    10.     if(prev == tail) 
    11.         tail = tmp;
    */
    bool done = false;
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
        done = insertAfterStep0(position, value, stepRequest, explanationText);
    }
    else if(step == 1) {
        done = forward ? insertAfterStep1(position, value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 2) {
        done = forward ? insertAfterStep2(position, value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 3) {
        done = forward ? insertAfterStep3(position, value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 4) {
        done = forward ? insertAfterStep4(position, value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 5) {
        done = forward ? insertAfterStep5(position, value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 6) {
        done = forward ? insertAfterStep6(position, value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 7) {
        done = forward ? insertAfterStep7(position, value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 8) {
        done = forward ? insertAfterStep8(position, value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 9) {
        done = forward ? insertAfterStep9(position, value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 10) {
        done = forward ? insertAfterStep10(position, value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 11) {
        done = forward ? insertAfterStep11(position, value, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    if(done) {
        PNode* tmp = dataStructurePointer->head;
        while(tmp != nullptr) {
            recordVector2(&tmp->center);
            tmp = tmp->pNext;
        }
        dataStructurePointer->reloadPositions();
    }
    return done;
}
bool PDSAnimation::insertAfterStep0(int position, int value, int stepRequest, string& explanationText) {
    // 00. Node* prev = head;
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        dataStructurePointer->animationPrev = dataStructurePointer->head;
        if(dataStructurePointer->head != nullptr) {
            dataStructurePointer->head->highlight = true;
        }
        makeVersion();
    }
    // Explanation
    if(dataStructurePointer->head != nullptr)
        explanationText = "prev = head.";
    else
        explanationText = "prev = head = nullptr.";
    // Wait request
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        if(dataStructurePointer->head != nullptr) {
            recordBool(&dataStructurePointer->head->highlight);
            dataStructurePointer->head->highlight = false;
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        recordInt(&dataStructurePointer->prevPosition);
        dataStructurePointer->prevPosition = 0;
        // Skip
        if(stepRequest == skipForward) {
            return insertAfterStep1(position, value, stepRequest, explanationText);
        }
    }
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertAfterStep1(int position, int value, int stepRequest, string& explanationText) {
    // for(int i = 0; i < position && prev != nullptr; i++)
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = dataStructurePointer->prevPosition < position && dataStructurePointer->animationPrev != nullptr;
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->takeCondition(condition);
        if(dataStructurePointer->animationPrev != nullptr) {
            recordBool(&dataStructurePointer->animationPrev->highlight);
            dataStructurePointer->animationPrev->highlight = true;
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition()) {
        explanationText = "i = " + to_string(dataStructurePointer->prevPosition) + " < " + to_string(position) 
        + " = position.\nprev is not null.\n" + "We continue to travel.";
    }
    else {
        if(dataStructurePointer->animationPrev == nullptr) {
            explanationText = "prev go out of the list.";
        }
        else {
            explanationText = "Reached the specified position.";
        }
    }
    // Wait request
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // Done algorithm
    if(done) {
        if(dataStructurePointer->animationPrev != nullptr) {
            recordBool(&dataStructurePointer->animationPrev->highlight);
            dataStructurePointer->animationPrev->highlight = false;
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return insertAfterStep2(position, value, stepRequest, explanationText);
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertAfterStep2(int position, int value, int stepRequest, string& explanationText) {
    // 02.     prev = prev->pNext;
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = taskManagementPointer->getCondition();
        if(condition == true) {
            recordPNodePointer(&dataStructurePointer->animationPrev, false);
            dataStructurePointer->animationPrev = dataStructurePointer->animationPrev->pNext;
            recordInt(&dataStructurePointer->prevPosition);
            dataStructurePointer->prevPosition++;
            if(dataStructurePointer->animationPrev != nullptr) {
                recordBool(&dataStructurePointer->animationPrev->highlight);
                dataStructurePointer->animationPrev->highlight = true;
            }
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition()) {
        explanationText = "prev traverses forward.";
    }
    else {
        explanationText = "Exit the loop.";
    }
    // Wait request
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        bool condition = taskManagementPointer->getCondition();
        if(condition == true) {
            if(dataStructurePointer->animationPrev != nullptr) {
                recordBool(&dataStructurePointer->animationPrev->highlight);
                dataStructurePointer->animationPrev->highlight = false;
            }
            recordFloat(&taskManagementPointer->time);
            recordInt(&taskManagementPointer->step);
            recordBool(&taskManagementPointer->taskDone);
            taskManagementPointer->prevStep();
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
            // Skip
            if(stepRequest == skipForward) {
                return insertAfterStep1(position, value, stepRequest, explanationText);
            }
        }
        else {
            recordFloat(&taskManagementPointer->time);
            recordInt(&taskManagementPointer->step);
            taskManagementPointer->nextStep();
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
            // Skip
            if(stepRequest == skipForward) {
                return insertAfterStep3(position, value, stepRequest, explanationText);
            }
        }
    }
    // Update time
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertAfterStep3(int position, int value, int stepRequest, string& explanationText) {
    // 03. if(prev != nullptr):
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = dataStructurePointer->animationPrev != nullptr;
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->takeCondition(condition);
        if(condition) {
            recordBool(&dataStructurePointer->animationPrev->highlight);
            dataStructurePointer->animationPrev->highlight = true;
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition())
        explanationText = "Found the indicated position.";
    else   
        explanationText = "Cound't find the indicated position.";
    // Wait request
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        bool condition = taskManagementPointer->getCondition();
        if(condition) {
            recordBool(&dataStructurePointer->animationPrev->highlight);
            dataStructurePointer->animationPrev->highlight = false;
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return insertAfterStep4(position, value, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertAfterStep4(int position, int value, int stepRequest, string& explanationText) {
    // 04.     Node* tmp = new Node(x);
    bool done = (waitRequest == false && (taskManagementPointer->getCondition() ? 
            dataStructurePointer->animationTmp != nullptr && dataStructurePointer->animationTmp->center == dataStructurePointer->animationTmp->centerFrom :
            taskManagementPointer->getTime() > PConstants::PAnimation::waitTime));
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = taskManagementPointer->getCondition();
        if(condition) {
            recordPNodePointer(&dataStructurePointer->animationTmp, true);
            dataStructurePointer->createNodeAfter(position, value);
            recordBool(&dataStructurePointer->animationTmp->highlight);
            dataStructurePointer->animationTmp->highlight = true;
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition())
        explanationText = "Create a new node.";
    // Wait request
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        bool condition = taskManagementPointer->getCondition();
        if(condition) {
            recordBool(&dataStructurePointer->animationTmp->highlight);
            dataStructurePointer->animationTmp->highlight = false;
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return insertAfterStep5(position, value, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertAfterStep5(int position, int value, int stepRequest, string& explanationText) {
    // 05.     tmp->pNext = prev->pNext;
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = taskManagementPointer->getCondition();
        if(condition) {
            recordPNodePointer(&dataStructurePointer->animationTmp->pNext, false);
            dataStructurePointer->animationTmp->pNext = dataStructurePointer->animationPrev->pNext;
            recordBool(&dataStructurePointer->animationTmp->lNext.highlight);
            dataStructurePointer->animationTmp->lNext.highlight = true;
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition())
        explanationText = "tmp->pNext points to prev->pNext.";
    // Wait request
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        bool condition = taskManagementPointer->getCondition();
        if(condition) {
            recordBool(&dataStructurePointer->animationTmp->lNext.highlight);
            dataStructurePointer->animationTmp->lNext.highlight = false;
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return insertAfterStep6(position, value, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertAfterStep6(int position, int value, int stepRequest, string& explanationText) {
    // 06.     prev->pNext = tmp;
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = taskManagementPointer->getCondition();
        if(condition) {
            recordPNodePointer(&dataStructurePointer->animationPrev->pNext, false);
            dataStructurePointer->animationPrev->pNext = dataStructurePointer->animationTmp;
            recordBool(&dataStructurePointer->animationPrev->lNext.highlight);
            dataStructurePointer->animationPrev->lNext.highlight = true;
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition()) {
        explanationText = "prev->pNext points to tmp.";
    }
    // Wait request
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        bool condition = taskManagementPointer->getCondition();
        if(condition) {
            recordBool(&dataStructurePointer->animationPrev->lNext.highlight);
            dataStructurePointer->animationPrev->lNext.highlight = false;
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return insertAfterStep7(position, value, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertAfterStep7(int position, int value, int stepRequest, string& explanationText) {
    // 07.     tmp->pPrev = prev;
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = taskManagementPointer->getCondition();
        if(condition) { 
            recordPNodePointer(&dataStructurePointer->animationTmp->pPrev, false);
            dataStructurePointer->animationTmp->pPrev = dataStructurePointer->animationPrev;
            recordBool(&dataStructurePointer->animationTmp->lPrev.highlight);
            dataStructurePointer->animationTmp->lPrev.highlight = true;
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition()) {
        explanationText = "tmp->pPrev points to prev";
    }
    // Wait request
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        bool condition = taskManagementPointer->getCondition();
        if(condition) {
            recordBool(&dataStructurePointer->animationTmp->lPrev.highlight);
            dataStructurePointer->animationTmp->lPrev.highlight = false;
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return insertAfterStep8(position, value, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertAfterStep8(int position, int value, int stepRequest, string& explanationText) {
    // 08.     if(tmp->pNext != nullptr) 
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = taskManagementPointer->getCondition();
        if(condition) {
            bool subConditon = dataStructurePointer->animationTmp->pNext != nullptr;
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->takeCondition(subConditon);
            if(subConditon) {
                recordBool(&dataStructurePointer->animationTmp->lNext.highlight);
                dataStructurePointer->animationTmp->lNext.highlight = true;
            }
        }
        makeVersion();
    }
    // Wait request
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // Explanation
    if(taskManagementPointer->getCondition(0)) {
        if(taskManagementPointer->getCondition(1)) {
            explanationText = "tmp->pNext is not null.";
        }
        else {
            explanationText = "tmp->pNext is null.";
        }
    }
    // End algorithm
    if(done) {
        bool condition = taskManagementPointer->getCondition();
        if(condition) {
            bool subCondition = taskManagementPointer->getCondition(1);
            if(subCondition) {
                recordBool(&dataStructurePointer->animationTmp->lNext.highlight);
                dataStructurePointer->animationTmp->lNext.highlight = false;
            }
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return insertAfterStep9(position, value, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertAfterStep9(int position, int value, int stepRequest, string& explanationText) {
    // 09.         tmp->pNext->pPrev = tmp;
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = taskManagementPointer->getCondition(0);
        if(condition) {
            bool con1 = taskManagementPointer->getCondition(1);
            if(con1) {
                recordPNodePointer(&dataStructurePointer->animationTmp->pNext->pPrev, false);
                dataStructurePointer->animationTmp->pNext->pPrev = dataStructurePointer->animationTmp;
                recordBool(&dataStructurePointer->animationTmp->pNext->lPrev.highlight);
                dataStructurePointer->animationTmp->pNext->lPrev.highlight = true;
            }
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition(0)) {
        if(taskManagementPointer->getCondition(1)) {
            explanationText = "tmp->pNext->pPrev points to tmp";
        }
    }
    // Wait request
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        bool con0 = taskManagementPointer->getCondition(0);
        if(con0) {
            bool con1 = taskManagementPointer->getCondition(1);
            if(con1) {
                recordBool(&dataStructurePointer->animationTmp->pNext->lPrev.highlight);
                dataStructurePointer->animationTmp->pNext->lPrev.highlight = false;
            }
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return insertAfterStep10(position, value, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertAfterStep10(int position, int value, int stepRequest, string& explanationText) {
    // 10.     if(prev == tail)
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con0 = taskManagementPointer->getCondition();
        if(con0) {
            bool con1 = dataStructurePointer->animationPrev == dataStructurePointer->tail;
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->takeCondition(con1);
            if(con1) {
                recordBool(&dataStructurePointer->animationPrev->highlight);
                dataStructurePointer->animationPrev->highlight = true;
            }
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition(0)) {
        if(taskManagementPointer->getCondition(1)) {
            explanationText = "prev is tail.";
        }
        else {
            explanationText = "prev is not tail.";
        }
    }
    // Wait request
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        bool con0 = taskManagementPointer->getCondition(0);
        if(con0) {
            bool con1 = taskManagementPointer->getCondition(1);
            if(con1) {
                dataStructurePointer->animationPrev->highlight = false;
            }
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return insertAfterStep11(position, value, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::insertAfterStep11(int position, int value, int stepRequest, string& explanationText) {
    // 11.         tail = tmp;
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con0 = taskManagementPointer->getCondition(0);
        if(con0) {
            bool con1 = taskManagementPointer->getCondition(1);
            if(con1) {
                recordPNodePointer(&dataStructurePointer->tail, false);
                dataStructurePointer->tail = dataStructurePointer->animationTmp;
                recordBool(&dataStructurePointer->tail->highlight);
                dataStructurePointer->tail->highlight = true;
            }
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition(0)) {
        if(taskManagementPointer->getCondition(1)) {
            explanationText = "Update tail.\nNew tail points to tmp.";
        }
    }
    // Wait request
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        bool con0 = taskManagementPointer->getCondition(0);
        if(con0) {
            bool con1 = taskManagementPointer->getCondition(1);
            if(con1) {
                recordBool(&dataStructurePointer->tail->highlight);
                dataStructurePointer->tail->highlight = false;
            }
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
        }
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->popCondition();
        recordInt(&dataStructurePointer->n);
        dataStructurePointer->addNumNode(1);
        recordPNodePointer(&dataStructurePointer->animationPrev, false);
        recordPNodePointer(&dataStructurePointer->animationTmp, false);
        dataStructurePointer->animationPrev = dataStructurePointer->animationTmp = nullptr;
        recordBool(&taskManagementPointer->taskDone);
        return true;
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}