#include "../header/PDSAnimation.h"

PDSAnimation::PDSAnimation(void) : 
    dataStructurePointer(nullptr), 
    taskManagementPointer(nullptr) {}

PDSAnimation::PDSAnimation(DoublyLinkedList * dataStructurePointer, PTaskManagement * taskManagementPointer) : 
    dataStructurePointer(dataStructurePointer), 
    taskManagementPointer(taskManagementPointer) {}

bool PDSAnimation::insertHead(int value) {
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
    // Get step id
    int step = taskManagementPointer->getStep();
    // Step 0
    if(step == 0) {
        bool doneAnimation0 = (dataStructurePointer->createdAnimationTmp() && 
            dataStructurePointer->animationTmpIsUpdated());
        // Create the node. If it is created, skip
        if(dataStructurePointer->createdAnimationTmp() == false) {
            // Create a node before the head node
            dataStructurePointer->createNodeBefore(0, value);
            // Highlight the new node
            dataStructurePointer->setHighlightAnimationTmp(true);
        }
        // Go to the next step
        if(doneAnimation0) {
            // Unhighlight the new node
            dataStructurePointer->setHighlightAnimationTmp(false);
            taskManagementPointer->nextStep();
        }
    }
    // Step 1
    else if(step == 1) {
        bool doneAnimation1 = taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime;
        // Do algorithm
        if(taskManagementPointer->getNumCondition() == 0) {
            // Check if the list is empty
            bool emptyList = dataStructurePointer->createdHead() == false;
            taskManagementPointer->takeCondition(emptyList);
            // Highlight the head node (if exists)
            if(dataStructurePointer->createdHead())
                dataStructurePointer->highlightHead();
        }
        // Update time
        taskManagementPointer->updateTime();
        // Go to the next step
        if(doneAnimation1) {
            // Unhighlight the head node (if exists)
            if(dataStructurePointer->createdHead())
                dataStructurePointer->unhighlightHead();
            taskManagementPointer->nextStep();
        }
    }
    // Step 2
    else if(step == 2) {
        // Done condition
        bool doneAnimation2 = taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime;
        // State of the list
        bool emptyList = taskManagementPointer->getCondition();
        // At time = 0, do back end
        if(taskManagementPointer->getTime() == 0.f) {
            // Algorithm for the empty list
            if(emptyList == true) {
                // head = tmp
                dataStructurePointer->assignAnimationTmpToHead();
            }
            // Algorithm for the non-empty list
            else {
                // head->pPrev = tmp
                dataStructurePointer->assignAnimationTmpToHeadPrev();
                // Animation
                // Highlight the link
                dataStructurePointer->setHighlightHeadPrevLink(true);
            }
        }
        // Update time
        taskManagementPointer->updateTime();
        // Go to the next step
        if(doneAnimation2) {
            if(emptyList == true) {}
            else {
                // Unhighlight the link
                dataStructurePointer->setHighlightHeadPrevLink(false);
            }
            taskManagementPointer->nextStep();
        }
    }
    // Step 3
    else if(step == 3) {
        // Done condition
        bool doneAnimation3 = taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime;
        // State of the list
        bool emptyList = taskManagementPointer->getCondition();
        if(taskManagementPointer->getTime() == 0.f) {
            // Algorithm for the empty list
            if(emptyList == true) {
                // tail = tmp
                dataStructurePointer->assignAnimationTmpToTail();
            }
            // Algorithm for the non-empty list
            else {
                // tmp->pNext = head
                dataStructurePointer->assignHeadToAnimationTmpNext();
                // Highlight the link
                dataStructurePointer->setHighlightAnimationTmpNextLink(true);
            }
        }
        // Update time
        taskManagementPointer->updateTime();
        // Go to the next step
        if(doneAnimation3 == true) {
            if(emptyList == true) {
                // animationTmp = nullptr
                dataStructurePointer->setAnimationTmpToNull();
                // n += 1
                dataStructurePointer->addNumNode(1);
                taskManagementPointer->popCondition();
                done = true;
            }
            else {
                // Unhighlight the link
                dataStructurePointer->setHighlightAnimationTmpNextLink(false);
            }
            taskManagementPointer->nextStep();
        }
    }
    // Step 4
    else if(step == 4) {
        // Done condition
        bool doneAnimation4 = (taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime);
        // Algorithm
        if(taskManagementPointer->getTime() == 0.f) {
            // head = tmp
            dataStructurePointer->assignAnimationTmpToHead();
        }
        // Update time
        taskManagementPointer->updateTime();
        // Go to the next step
        if(doneAnimation4) {
            // animationTmp = nullptr
            dataStructurePointer->setAnimationTmpToNull();
            // n += 1
            dataStructurePointer->addNumNode(1);
            taskManagementPointer->popCondition();
            done = true;
        }
    }
    else {
        cerr << "Input wrong step in DS1::insertHead(value, step)\n";
        exit(0);
    }
    // Check if the progress is done
    return done;
}

bool PDSAnimation::insertTail(int value) {
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
    // Track if the progress is done
    bool done = false;
    // Get step id
    int step = taskManagementPointer->getStep();
    // Step 0
    if(step == 0) {
        bool doneAnimation0 = (dataStructurePointer->createdAnimationTmp() && 
            dataStructurePointer->animationTmpIsUpdated());
        // Create the node. If it is created, skip
        if(dataStructurePointer->createdAnimationTmp() == false) {
            // Create a node before the head node
            dataStructurePointer->createNodeAfter(dataStructurePointer->getNumNode() - 1, value);
            // Highlight the new node
            dataStructurePointer->setHighlightAnimationTmp(true);
        }
        // Go to the next step
        if(doneAnimation0) {
            // Unhighlight the new node
            dataStructurePointer->setHighlightAnimationTmp(false);
            taskManagementPointer->nextStep();
        }
    }
    // Step 1
    else if(step == 1) {
        bool doneAnimation1 = taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime;
        // Do algorithm
        if(taskManagementPointer->getNumCondition() == 0) {
            // Check if the list is empty
            bool emptyList = dataStructurePointer->createdHead() == false;
            taskManagementPointer->takeCondition(emptyList);
            // Highlight the head node (if exists)
            if(dataStructurePointer->createdHead())
                dataStructurePointer->highlightHead();
        }
        // Update time
        taskManagementPointer->updateTime();
        // Go to the next step
        if(doneAnimation1) {
            // Unhighlight the head node (if exists)
            if(dataStructurePointer->createdHead())
                dataStructurePointer->unhighlightHead();
            taskManagementPointer->nextStep();
        }
    }
    // Step 2
    else if(step == 2) {
        // Done condition
        bool doneAnimation2 = taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime;
        // State of the list
        bool emptyList = taskManagementPointer->getCondition();
        // At time = 0, do back end
        if(taskManagementPointer->getTime() == 0.f) {
            // Algorithm for the empty list
            if(emptyList == true) {
                // head = tmp
                dataStructurePointer->assignAnimationTmpToHead();
            }
            // Algorithm for the non-empty list
            else {
                // tail->pNext = tmp
                dataStructurePointer->assignAnimationTmpToTailNext();
                // Animation
                // Highlight the link
                dataStructurePointer->setHighlightTailNextLink(true);
            }
        }
        // Update time
        taskManagementPointer->updateTime();
        // Go to the next step
        if(doneAnimation2) {
            if(emptyList == true) {}
            else {
                // Unhighlight the link
                dataStructurePointer->setHighlightTailNextLink(false);
            }
            taskManagementPointer->nextStep();
        }
    }
    // Step 3
    else if(step == 3) {
        // Done condition
        bool doneAnimation3 = taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime;
        // State of the list
        bool emptyList = taskManagementPointer->getCondition();
        if(taskManagementPointer->getTime() == 0.f) {
            // Algorithm for the empty list
            if(emptyList == true) {
                // tail = tmp
                dataStructurePointer->assignAnimationTmpToTail();
            }
            // Algorithm for the non-empty list
            else {
                // tmp->pPrev = tail
                dataStructurePointer->assignTailToAnimationTmpPrev();
                // Animation
                // Highlight the link
                dataStructurePointer->setHighlightAnimationTmpPrevLink(true);
            }
        }
        // Update time
        taskManagementPointer->updateTime();
        // Go to the next step
        if(doneAnimation3 == true) {
            if(emptyList == true) {
                // Algorithm for true end here
                // animationTmp = nullptr
                dataStructurePointer->setAnimationTmpToNull();
                // n += 1
                dataStructurePointer->addNumNode(1);
                taskManagementPointer->popCondition();
                done = true;
            }
            else {
                // Unhighlight the link
                dataStructurePointer->setHighlightAnimationTmpPrevLink(false);
            }
            taskManagementPointer->nextStep();
        }
    }
    // Step 4
    else if(step == 4) {
        // Done condition
        bool doneAnimation4 = (taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime);
        // Algorithm
        if(taskManagementPointer->getTime() == 0.f) {
            // tail = tmp
            dataStructurePointer->assignAnimationTmpToTail();
        }
        // Update time
        taskManagementPointer->updateTime();
        // Go to the next step
        if(doneAnimation4) {
            // animationTmp = nullptr
            dataStructurePointer->setAnimationTmpToNull();
            // n += 1
            dataStructurePointer->addNumNode(1);
            taskManagementPointer->popCondition();
            done = true;
        }
    }
    else {
        cerr << "Input wrong step in DS1::insertTail(value, step)\n";
        exit(0);
    }
    // Check if the progress is done
    return done;
}

bool PDSAnimation::insertAfter(int position, int value) {
    /*
    Code:
        Node* prev = head;
        for(int i = 0; i < position && prev != nullptr; i++)
            prev = prev->pNext;
        if(prev != nullptr) {
            Node* tmp = new Node(x);
            tmp->pNext = prev->pNext;
            prev->pNext = tmp;
            tmp->pPrev = prev;
            if(tmp->pNext != nullptr) tmp->pNext->pPrev = tmp;
            if(prev == tail) tail = tmp;
        }
    Pseudo code:
    Step 0.    AssignHeadToAnimationPrev : prev = head
    Step 1.    TraverseAnimationPrev : for(int i = 0; i < position && prev != nullptr; i++) 
                                prev = prev->pNext
    Step 2.    CheckFoundPrev : if(prev != nullptr)
    Found prev : (true)
        Step 3. CreateNodeAfter : tmp = new Node(x)
        Step 4. AssignAnimationPrevNextToAnimationTmpNext : tmp->pNext = prev->pNext
        Step 5. AssignAnimationTmpToAnimationPrevNext : pre->pNext = tmp
        Step 6. AssignAnimationPrevToAnimationTmpPrev : tmp->pPrev = pre
        Step 7. AssignAnimationTmpToAnimationTmpNextPrev : tmp->pNext->pPrev = tmp
        Step 8. CheckIfAnimationPrevEqualToTail
        Step 9. AssignAnimationTmpToTail
        End algorithm, pop conditionStack
    Not found prev : (false) : End algorithm, pop conditionStack
    */
    // Track if the progress is done
    bool done = false;
    // Get step id
    int step = taskManagementPointer->getStep();
    // Step 0
    if(step == 0) {
        // Done condition
        bool doneAnimation0 = taskManagementPointer->getTime() > PConstants::PAnimation::waitTime;
        // Algorithm step 0
        if(taskManagementPointer->getTime() == 0.f) {
            dataStructurePointer->assignHeadToAnimationPrev();
            // Highlight
            dataStructurePointer->setHighlightAnimationPrev(true);
        }
        // Update time
        taskManagementPointer->updateTime();
        // Go to the next step
        if(doneAnimation0) {
            // Unhighlight
            dataStructurePointer->setHighlightAnimationPrev(false);
            taskManagementPointer->nextStep();
        }
    }
    // Step 1 
    else if(step == 1) {
        // Done condition
        bool doneAnimation1 = dataStructurePointer->traversePrevDone(position);
        // Loop condition
        bool doneLoop = taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime;
        // Algorithm step 1
        if(taskManagementPointer->getTime() == 0.f) {
            // Unhighlight prev
            dataStructurePointer->setHighlightAnimationPrev(false);
            dataStructurePointer->traversePrev(position);
            // Highlight prev
            dataStructurePointer->setHighlightAnimationPrev(true);
        }
        
        // Update time
        taskManagementPointer->updateTime();
        // Loop
        if(doneAnimation1 == false && doneLoop == true) {
            taskManagementPointer->redoLoop();
        }
        // Go to the next step
        if(doneAnimation1) {
            // Unhighlight prev
            dataStructurePointer->setHighlightAnimationPrev(false);
            taskManagementPointer->nextStep();
        }
    } 
    // Step 2
    else if(step == 2) {
        // Step condition
        bool doneAnimation2 = taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime;
        // Algorithm step 2
        if(taskManagementPointer->getTime() == 0.f) {
            bool condition = dataStructurePointer->createdAnimationPrev();
            taskManagementPointer->takeCondition(condition);
            // Highlight the prev node
            if(condition) {
                dataStructurePointer->setHighlightAnimationPrev(true);
            }
        }
        // Update time
        taskManagementPointer->updateTime();
        // Go to the next step
        if(doneAnimation2) {
            // Unhighlight the prev node
            bool condition = taskManagementPointer->getCondition();
            if(condition) {
                dataStructurePointer->setHighlightAnimationPrev(false);
            }
            else {
                dataStructurePointer->setAnimationPrevToNull();
                taskManagementPointer->popCondition();
                done = true;
            }
            taskManagementPointer->nextStep();
        }
    }
    // Step 3
    else if(step == 3) {
        // Done condition
        bool doneAnimation3 = (dataStructurePointer->createdAnimationTmp() && dataStructurePointer->animationTmpIsUpdated());
        // Algorithm for step 3
        if(dataStructurePointer->createdAnimationTmp() == false) {
            // tmp = new Node(x)
            dataStructurePointer->createNodeAfter(position, value);
            dataStructurePointer->setHighlightAnimationTmp(true);
        }
        // Update time
        taskManagementPointer->updateTime();
        // Go to the next step
        if(doneAnimation3) {
            dataStructurePointer->setHighlightAnimationTmp(false);
            taskManagementPointer->nextStep();
        }
    }
    // Step 4
    else if(step == 4) {
        bool doneAnimation4 = taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime;

        if(taskManagementPointer->getTime() == 0.f) {
            // tmp->pNext = prev->pNext
            dataStructurePointer->assignAnimationPrevNextToAnimationTmpNext();
            // Highlight the link
            dataStructurePointer->setHighlightAnimationTmpNextLink(true);
        }

        taskManagementPointer->updateTime();
        if(doneAnimation4) {
            // Unhighlight the link
            dataStructurePointer->setHighlightAnimationTmpNextLink(false);
            taskManagementPointer->nextStep();
        }
    }
    // Step 5
    else if(step == 5) {
        bool doneAnimation5 = taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime;

        if(taskManagementPointer->getTime() == 0.f) {
            // prev->pNext = tmp
            dataStructurePointer->assignAnimationTmpToAnimationPrevNext();
            // Highlight
            dataStructurePointer->setHighlightAnimationPrevNextLink(true);
        }

        taskManagementPointer->updateTime();
        if(doneAnimation5) {
            // Unighlight
            dataStructurePointer->setHighlightAnimationPrevNextLink(false);
            taskManagementPointer->nextStep();
        }
    }
    // Step 6
    else if(step == 6) {
        bool doneAnimation6 = taskManagementPointer->getTime() >= PConstants::PAnimation::waitTime;

        if(taskManagementPointer->getTime() == 0.f) {
            // tmp->pPrev = prev
            dataStructurePointer->assignAnimationPrevToAnimationTmpPrev();
            // Highlight
            dataStructurePointer->setHighlightAnimationTmpPrevLink(true);
        }

        taskManagementPointer->updateTime();
        if(doneAnimation6) {
            // Unighlight
            dataStructurePointer->setHighlightAnimationTmpPrevLink(false);
            taskManagementPointer->nextStep();
        }
    }
    // Step 7
    else if(step == 7) {
        bool doneAnimation7 = taskManagementPointer->getTime() > PConstants::PAnimation::waitTime;

        if(taskManagementPointer->getTime() == 0.f) {
            // tmp->pNext->pPrev = tmp
            dataStructurePointer->assignAnimationTmpToAnimationTmpNextPrev();
            // Highlight tmp->pNext->pPrev
            dataStructurePointer->setHighlightAnimationTmpNextPrevLink(true);
        }

        taskManagementPointer->updateTime();
        if(doneAnimation7) {
            // Unighlight
            dataStructurePointer->setHighlightAnimationTmpNextPrevLink(false);
            taskManagementPointer->nextStep();
        }
    }
    // Step 8
    else if(step == 8) {
        bool doneAnimation8 = taskManagementPointer->getTime() > PConstants::PAnimation::waitTime;

        if(taskManagementPointer->getTime() == 0.f) {
            bool condition = dataStructurePointer->isAnimationPrevTail();
            taskManagementPointer->takeCondition(condition);
            // Highlight
            dataStructurePointer->setHighlightAnimationPrev(true);
        }

        taskManagementPointer->updateTime();
        if(doneAnimation8) {
            // Unighlight
            dataStructurePointer->setHighlightAnimationPrev(false);
            taskManagementPointer->nextStep();
        }
    }
    // Step 9
    else if(step == 9) {
        bool doneAnimation9 = taskManagementPointer->getTime() > PConstants::PAnimation::waitTime;

        if(taskManagementPointer->getTime() == 0.f) {
            bool condition = taskManagementPointer->getCondition();
            if(condition) {
                // tmp = tail
                dataStructurePointer->assignAnimationTmpToTail();
            }
        }

        taskManagementPointer->updateTime();
        if(doneAnimation9) {
            // Pop condition stack (2)
            for(int i = 0; i < 2; i++) taskManagementPointer->popCondition();
            // tmp = prev = nullptr
            dataStructurePointer->setAnimationTmpToNull();
            dataStructurePointer->setAnimationPrevToNull();
            // End the algorithm
            done = true;
        }
    }
    return done;
}