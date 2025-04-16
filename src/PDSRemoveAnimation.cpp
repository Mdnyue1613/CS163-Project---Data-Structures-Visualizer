#include "../header/PDSAnimation.h"

bool PDSAnimation::remove(int position, int stepRequest, string& explanationText) {
    /*
    00.    if(position < 0 || position >= n) : return
    01.    if(position == 0) :
    02.        tmp = head
    03.        head = head->pNext
    04.        if(head != nullptr) : head->pPrev = nullptr
    04.        else tail = nullptr
    05.        delete tmp
           else 
    02.        if(position == n - 1) :
    03.            tmp = tail
    04.            tail = tail->pPrev
    05.            if(tail != nullptr) : tail->pNext = nullptr
    05.            else head = nullptr
    06.            delete tmp
               else :
    03.            prev = head
    04.            for(int i = 0; i < position - 1 && prev != nullptr; i++)
    05.                prev = prev->pNext
    06.            if(prev != nullptr && prev->pNext != nullptr) :
    07.                tmp = prev->pNext
    08.                prev->pNext = tmp->pNext
    09.                tmp->pNext->pPrev = prev
    10.                delete tmp
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
        done = forward ? removeStep0(position, stepRequest, explanationText) : false;
    }
    else if(step == 1) {
        done = forward ? removeStep1(position, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 2) {
        done = forward ? removeStep2(position, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 3) {
        done = forward ? removeStep3(position, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 4) {
        done = forward ? removeStep4(position, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 5) {
        done = forward ? removeStep5(position, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 6) {
        done = forward ? removeStep6(position, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 7) {
        done = forward ? removeStep7(position, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 8) {
        done = forward ? removeStep8(position, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 9) {
        done = forward ? removeStep9(position, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    else if(step == 10) {
        done = forward ? removeStep10(position, stepRequest, explanationText) : undoVersion(stepRequest);
    }
    return done;
}

bool PDSAnimation::removeStep0(int position, int stepRequest, string& explanationText) {
    cout << "removeStep0\n";
    // 00.    if(position < 0 || position >= n) : return
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = position < 0 || position >= dataStructurePointer->getNumNode();
        if(condition) {
            return true;
        }
        makeVersion();
    }
    // Explanation
    explanationText = "Check if the position is valid.";
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return removeStep1(position, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::removeStep1(int position, int stepRequest, string& explanationText) {
    cout << "removeStep1\n";
    // 01.    if(position == 0) :
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool condition = position == 0;
        recordVectorBool(&taskManagementPointer->conditionStack);
        taskManagementPointer->takeCondition(condition);
        makeVersion();
    }
    // Explanation
    explanationText = "Check if the position is head's position.";
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return removeStep2(position, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::removeStep2(int position, int stepRequest, string& explanationText) {
    cout << "removeStep2\n";
    // 02. true : { tmp == head }; false : { if position == n - 1 }
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con0 = taskManagementPointer->getCondition(0);
        if(con0) {
            recordPNodePointer(&dataStructurePointer->animationTmp, false);
            dataStructurePointer->animationTmp = dataStructurePointer->head;
            recordBool(&dataStructurePointer->animationTmp->highlight);
            dataStructurePointer->animationTmp->highlight = true;
        }
        else {
            bool con1 = position == dataStructurePointer->getNumNode() - 1;
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->takeCondition(con1);
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition(0)) {
        explanationText = "tmp points to head.";
    }
    else {
        explanationText = "Check if the position is tail's position.";
    }
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        bool con0 = taskManagementPointer->getCondition(0);
        if(con0) {
            recordBool(&dataStructurePointer->animationTmp->highlight);
            dataStructurePointer->animationTmp->highlight = false;
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return removeStep3(position, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::removeStep3(int position, int stepRequest, string& explanationText) {
    cout << "removeStep3\n";
    // 03. true : { head = head->pNext }; false : { true : { tmp = tail }; false : { prev = head };};
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con0 = taskManagementPointer->getCondition(0);
        if(con0) {
            recordPNodePointer2(&dataStructurePointer->head, &dataStructurePointer->animationTmp);
            dataStructurePointer->head = dataStructurePointer->head->pNext;
            if(dataStructurePointer->head != nullptr) {
                recordBool(&dataStructurePointer->head->highlight);
                dataStructurePointer->head->highlight = true;
            }
        }
        else {
            bool con1 = taskManagementPointer->getCondition(1);
            if(con1) {
                recordPNodePointer(&dataStructurePointer->animationTmp, false);
                dataStructurePointer->animationTmp = dataStructurePointer->tail;
                recordBool(&dataStructurePointer->animationTmp->highlight);
                dataStructurePointer->animationTmp->highlight = true;
            }
            else {
                recordPNodePointer(&dataStructurePointer->animationPrev, false);
                dataStructurePointer->animationPrev = dataStructurePointer->head;
                recordBool(&dataStructurePointer->animationPrev->highlight);
                dataStructurePointer->animationPrev->highlight = true;
            }
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition(0)) {
        explanationText = "head shifts forward.";
    }
    else if(taskManagementPointer->getCondition(1)) {
        explanationText = "tmp points to tail.";
    }
    else {
        explanationText = "prev points to head.";
    }
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        bool con0 = taskManagementPointer->getCondition(0);
        if(con0) {
            if(dataStructurePointer->head != nullptr) {
                recordBool(&dataStructurePointer->head->highlight);
                dataStructurePointer->head->highlight = false;
            }
        }
        else {
            bool con1 = taskManagementPointer->getCondition(1);
            if(con1) {
                recordBool(&dataStructurePointer->animationTmp->highlight);
                dataStructurePointer->animationTmp->highlight = false;
            }
            else {
                recordBool(&dataStructurePointer->animationPrev->highlight);
                dataStructurePointer->animationPrev->highlight = false;
                recordInt(&dataStructurePointer->prevPosition);
                dataStructurePointer->prevPosition = 0;
            }
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return removeStep4(position, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::removeStep4(int position, int stepRequest, string& explanationText) {
    cout << "removeStep4\n";
    // 04. true : { if(head != nullptr) : head->pPrev = nullptr else tail = nullptr } ; false : { true : { tail = tail->pPrev} ; false : { for(int i = 0; i < position - 1 && prev != nullptr; i++) } }
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con0 = taskManagementPointer->getCondition(0);
        if(con0) {
            if(dataStructurePointer->head != nullptr) {
                recordPNodePointer2(&dataStructurePointer->head->pPrev, &dataStructurePointer->animationTmp);
                dataStructurePointer->head->pPrev = nullptr;
            }
            else {
                recordPNodePointer2(&dataStructurePointer->tail, &dataStructurePointer->animationTmp);
                dataStructurePointer->tail = nullptr;
            }
        }
        else {
            bool con1 = taskManagementPointer->getCondition(1);
            if(con1) {
                recordPNodePointer2(&dataStructurePointer->tail, &dataStructurePointer->animationTmp);
                dataStructurePointer->tail = dataStructurePointer->tail->pPrev;
                if(dataStructurePointer->tail != nullptr) {
                    recordBool(&dataStructurePointer->tail->highlight);
                    dataStructurePointer->tail->highlight = true;
                }
            }
            else {
                bool con2 = dataStructurePointer->prevPosition < position - 1 && dataStructurePointer->animationPrev != nullptr;
                recordVectorBool(&taskManagementPointer->conditionStack);
                taskManagementPointer->takeCondition(con2);
                if(con2) {
                    recordBool(&dataStructurePointer->animationPrev->highlight);
                    dataStructurePointer->animationPrev->highlight = true;
                }
            }
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition(0)) {
        if(dataStructurePointer->head != nullptr) {
            explanationText = "Set head->pPrev to nullptr.";
        }
        else {
            explanationText = "Set tail to nullptr.";
        }
    }
    else if(taskManagementPointer->getCondition(1)) {
        if(dataStructurePointer->tail != nullptr) {
            explanationText = "tail shifts backward.";
        }
    }
    else {
        if(taskManagementPointer->getCondition(2)) {
            explanationText = "Haven't reached the position yet.";
        }
        else {
            if(dataStructurePointer->animationPrev == nullptr)
                explanationText = "prev is nullptr";
            else
                explanationText = "Reached the position.";
        }
    }
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        bool con0 = taskManagementPointer->getCondition(0);
        if(con0) {}
        else {
            bool con1 = taskManagementPointer->getCondition(1);
            if(con1) {
                if(dataStructurePointer->tail != nullptr) {
                    recordBool(&dataStructurePointer->tail->highlight);
                    dataStructurePointer->tail->highlight = false;
                }
            }
            else {
                bool con2 = taskManagementPointer->getCondition(2);
                if(con2) {
                    recordBool(&dataStructurePointer->animationPrev->highlight);
                    dataStructurePointer->animationPrev->highlight = false;
                }
            }
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return removeStep5(position, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::removeStep5(int position, int stepRequest, string& explanationText) {
    cout << "removeStep5\n";
    // 05. true :
    //      delete tmp
    //     false :
    //         true:
    //             if(tail != nullptr) tail->pNext = nullptr
    //             else head = nullptr
    //         false:
    //             true:
    //                 prev = prev->pNext
    //             false:
    //                 break;
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con0 = taskManagementPointer->getCondition(0);
        if(con0) {
            recordDeletePNodePointer(&dataStructurePointer->animationTmp);
            delete dataStructurePointer->animationTmp;
            dataStructurePointer->animationTmp = nullptr;
        }
        else {
            bool con1 = taskManagementPointer->getCondition(1);
            if(con1) {
                if(dataStructurePointer->tail != nullptr) {
                    recordPNodePointer2(&dataStructurePointer->tail->pNext, &dataStructurePointer->animationTmp);
                    dataStructurePointer->tail->pNext = nullptr;
                }
                else {
                    recordPNodePointer2(&dataStructurePointer->head, &dataStructurePointer->animationTmp);
                    dataStructurePointer->head = nullptr;
                }
            }
            else {
                bool con2 = taskManagementPointer->getCondition(2);
                if(con2) {
                    recordPNodePointer(&dataStructurePointer->animationPrev, false);
                    dataStructurePointer->animationPrev = dataStructurePointer->animationPrev->pNext;
                    if(dataStructurePointer->animationPrev != nullptr) {
                        recordBool(&dataStructurePointer->animationPrev->highlight);
                        dataStructurePointer->animationPrev->highlight = true;
                    }
                }
            }
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition(0)) {
        explanationText = "Delete tmp.";
    }
    else if(taskManagementPointer->getCondition(1)) {
        if(dataStructurePointer->tail != nullptr) {
            explanationText = "Set tail->pNext to nullptr.";
        }
        else {
            explanationText = "Set head to nullptr.";
        }
    }
    else {
        if(taskManagementPointer->getCondition(2)) {
            explanationText = "Traverse prev.";
        }
        else {
            explanationText = "Exit the loop.";
        }
    }
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        bool con0 = taskManagementPointer->getCondition(0);
        if(con0) {
            recordInt(&dataStructurePointer->n);
            dataStructurePointer->addNumNode(-1);
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->popCondition();
            recordBool(&taskManagementPointer->taskDone);
            return true;
        }
        else {
            bool con1 = taskManagementPointer->getCondition(1);
            if(con1) {
                recordFloat(&taskManagementPointer->time);
                recordInt(&taskManagementPointer->step);
                taskManagementPointer->nextStep();
                // Skip
                if(stepRequest == skipForward) {
                    return removeStep6(position, stepRequest, explanationText);
                }
            }
            else {
                bool con2 = taskManagementPointer->getCondition(2);
                if(con2) {
                    if(dataStructurePointer->animationPrev != nullptr) {
                        recordBool(&dataStructurePointer->animationPrev->highlight);
                        dataStructurePointer->animationPrev->highlight = false;
                    }
                    recordInt(&dataStructurePointer->prevPosition);
                    dataStructurePointer->prevPosition++;
                    recordBool(&taskManagementPointer->taskDone);
                    recordFloat(&taskManagementPointer->time);
                    recordInt(&taskManagementPointer->step);
                    taskManagementPointer->prevStep();
                    recordVectorBool(&taskManagementPointer->conditionStack);
                    taskManagementPointer->popCondition();
                    // Skip
                    if(stepRequest == skipForward) {
                        return removeStep4(position, stepRequest, explanationText);
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
                        return removeStep6(position, stepRequest, explanationText);
                    }
                }
            }
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::removeStep6(int position, int stepRequest, string& explanationText) {
    cout << "removeStep6\n";
    /*
    False:
        True: 
            delete tmp
        False:
            if(prev != nullptr && prev->pNext != nullptr)
    */
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        bool con1 = taskManagementPointer->getCondition(1);
        if(con1) {
            recordDeletePNodePointer(&dataStructurePointer->animationTmp);
            delete dataStructurePointer->animationTmp;
            dataStructurePointer->animationTmp = nullptr;
        }
        else {
            bool con2 = dataStructurePointer->animationPrev != nullptr && dataStructurePointer->animationPrev->pNext != nullptr;
            recordVectorBool(&taskManagementPointer->conditionStack);
            taskManagementPointer->takeCondition(con2);
            if(con2) {
                recordBool(&dataStructurePointer->animationPrev->highlight);
                dataStructurePointer->animationPrev->highlight = true;
            }
        }
        makeVersion();
    }
    // Explanation
    if(taskManagementPointer->getCondition(1)) {
        explanationText = "Delete tmp.";
    }
    else {
        if(taskManagementPointer->getCondition(2)) {
            explanationText = "Found the node to be removed.";
        }
        else {
            explanationText = "Couldn't find the node to be removed.";
        }
    }
    // Skip
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        bool con1 = taskManagementPointer->getCondition(1);
        if(con1) {
            recordInt(&dataStructurePointer->n);
            dataStructurePointer->addNumNode(-1);
            recordVectorBool(&taskManagementPointer->conditionStack);
            for(int i = 0; i < 2; i++)
                taskManagementPointer->popCondition();
            recordBool(&taskManagementPointer->taskDone);
            return true;
        }
        else {
            bool con2 = taskManagementPointer->getCondition(2);
            if(con2) {
                recordBool(&dataStructurePointer->animationPrev->highlight);
                dataStructurePointer->animationPrev->highlight = false;
                recordFloat(&taskManagementPointer->time);
                recordInt(&taskManagementPointer->step);
                taskManagementPointer->nextStep();
                // Skip
                if(stepRequest == skipForward) {
                    return removeStep7(position, stepRequest, explanationText);
                }
            }
            else {
                recordPNodePointer(&dataStructurePointer->animationPrev, false);
                dataStructurePointer->animationPrev = nullptr;
                recordVectorBool(&taskManagementPointer->conditionStack);
                for(int i = 0; i < 3; i++) 
                    taskManagementPointer->popCondition();
                recordInt(&dataStructurePointer->prevPosition);
                dataStructurePointer->prevPosition = 0;
                recordBool(&taskManagementPointer->taskDone);
                return true;
            }
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::removeStep7(int position, int stepRequest, string& explanationText) {
    cout << "removeStep7\n";
    /*
        False:
            False:
                True:
                    tmp = prev->pNext
    */
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        recordPNodePointer(&dataStructurePointer->animationTmp, false);
        dataStructurePointer->animationTmp = dataStructurePointer->animationPrev->pNext;
        recordBool(&dataStructurePointer->animationTmp->highlight);
        dataStructurePointer->animationTmp->highlight = true;
        makeVersion();
    }
    // Explanation
    explanationText = "tmp points to prev->pNext.";
    // Skip animation
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
            return removeStep8(position, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::removeStep8(int position, int stepRequest, string& explanationText) {
    cout << "removeStep8\n";
    /*
        False:
            False:
                True:
                    prev->pNext = tmp->pNext
    */
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        recordPNodePointer2(&dataStructurePointer->animationPrev->pNext, &dataStructurePointer->animationTmp);
        dataStructurePointer->animationPrev->pNext = dataStructurePointer->animationTmp->pNext;
        if(dataStructurePointer->animationPrev->pNext != nullptr) {
            recordBool(&dataStructurePointer->animationPrev->lNext.highlight);
            dataStructurePointer->animationPrev->lNext.highlight = true;
        }
        makeVersion();
    }
    // Explanation
    explanationText = "prev->pNext points to tmp->pNext.";
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        if(dataStructurePointer->animationPrev->pNext != nullptr) {
            recordBool(&dataStructurePointer->animationPrev->lNext.highlight);
            dataStructurePointer->animationPrev->lNext.highlight = false;
        }
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return removeStep9(position, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::removeStep9(int position, int stepRequest, string& explanationText) {
    cout << "removeStep9\n";
    /*
        False:
            False:
                True:
                    tmp->pNext->pPrev = prev
    */
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        recordPNodePointer2(&dataStructurePointer->animationTmp->pNext->pPrev, &dataStructurePointer->animationTmp);
        dataStructurePointer->animationTmp->pNext->pPrev = dataStructurePointer->animationPrev;
        recordBool(&dataStructurePointer->animationTmp->pNext->lPrev.highlight);
        dataStructurePointer->animationTmp->pNext->lPrev.highlight = true;
        makeVersion();
    }
    // Explanation
    explanationText = "tmp->pNext->pPrev points to prev.";
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        recordBool(&dataStructurePointer->animationTmp->pNext->lPrev.highlight);
        dataStructurePointer->animationTmp->pNext->lPrev.highlight = false;
        recordFloat(&taskManagementPointer->time);
        recordInt(&taskManagementPointer->step);
        taskManagementPointer->nextStep();
        // Skip
        if(stepRequest == skipForward) {
            return removeStep10(position, stepRequest, explanationText);
        }
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}
bool PDSAnimation::removeStep10(int position, int stepRequest, string& explanationText) {
    cout << "removeStep10\n";
    /*
        False:
            False:
                True:
                    delete tmp
    */
    bool done = (waitRequest == false && taskManagementPointer->getTime() > PConstants::PAnimation::waitTime);
    // Begin algorithm
    if(taskManagementPointer->getTime() == 0.f) {
        recordDeletePNodePointer(&dataStructurePointer->animationTmp);
        delete dataStructurePointer->animationTmp;
        dataStructurePointer->animationTmp = nullptr;
        makeVersion();
    }
    // Explanation
    explanationText = "Delete tmp.";
    // Skip animation
    if(stepRequest == goForward || stepRequest == skipForward) {
        done = true;
    }
    // End algorithm
    if(done) {
        recordInt(&dataStructurePointer->n);
        dataStructurePointer->addNumNode(-1);
        recordVectorBool(&taskManagementPointer->conditionStack);
        for(int i = 0; i < 3; i++)
            taskManagementPointer->popCondition();
        recordPNodePointer(&dataStructurePointer->animationPrev, false);
        dataStructurePointer->animationPrev = nullptr;
        recordBool(&taskManagementPointer->taskDone);
        recordInt(&dataStructurePointer->prevPosition);
        dataStructurePointer->prevPosition = 0;
        return true;
    }
    // Update
    else taskManagementPointer->updateTime();
    return false;
}