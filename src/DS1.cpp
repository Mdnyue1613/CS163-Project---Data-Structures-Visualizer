#include "../header/DS1.h"

DS1::DS1(void) :
    functionArea(PConstants::PFunctionArea::pos, PConstants::PFunctionArea::size),
    stepByStepMenu(PConstants::PStepByStepMenu::pos, PConstants::PStepByStepMenu::size),
    titleBox(PConstants::PTitleBar::pos, PConstants::PTitleBar::size, PConstants::PTitleBar::outlineThickness, PConstants::PTitleBar::boxColor, PConstants::PTitleBar::outlineColor, "DOUBLY LINKED LIST", PConstants::PTitleBar::textSize),
    taskManagement(),
    randomGenerator(),
    explanationArea(),
    notificationBox(),
    pseudoCode() {
        doublyLinkedList = new DoublyLinkedList();
        animationManagement = PDSAnimation(doublyLinkedList, &taskManagement);
        functionArea.menuUpdate.dataStructurePointer = doublyLinkedList;
    }

DS1::~DS1(void) {
    if(doublyLinkedList != nullptr)
        delete doublyLinkedList;
}

void DS1::prepare(void) {
    functionArea.prepare();
    stepByStepMenu.prepare();
    notificationBox.prepare();
}

void DS1::update(void) {
    if(notificationBox.notificationText.size() > 0) {
        notificationBox.update();
    }

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
        if(done) {
            taskManagement.endTask();
        }
    }
    // Inserting request
    else if(type == Insert) {
        bool done = operateInsert(request, stepRequest, explanationText);
        if(done) {
            taskManagement.endTask();
        }
    }
    else if(type == Remove) {
        bool done = operateRemove(request, stepRequest, explanationText);
        if(done) {
            taskManagement.endTask();
        }
    }
    else if(type == Search) {
        bool done = operateSearch(request, stepRequest, explanationText);
        if(done) {
            taskManagement.endTask();
        }
    }
    else if(type == Update) {
        bool done = operateUpdate(doublyLinkedList->animationChosen, request, stepRequest, explanationText);
        if(done) {
            taskManagement.endTask();
        }
    }
    else if(type == NoTask) {
    }

    // Update explanation area
    explanationArea.update(explanationText);

    // Update linked list
    doublyLinkedList->update(taskManagement.doneTask());
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

    // Draw pseudo code
    pseudoCode.draw();

    // Draw Data Structure
    doublyLinkedList->draw(taskManagement.doneTask());

    // Notification text
    if(notificationBox.notificationText.size() > 0) {
        notificationBox.draw();
    }
}

bool DS1::operateInitialize(vector<string>& request, int stepRequest, string& explanationText) {
    if(taskManagement.doneTask())
        return true;
    string requestType = request[1];
    if(requestType == "random") {
        if((int)request.size() == 2) {
            doublyLinkedList->randomInitializer(randomGenerator.random(1, 35));
        }
        else {
            int value = notificationBox.getOneNum(request[2], 0, 100);
            if(notificationBox.notificationText == "Valid") {
                doublyLinkedList->randomInitializer(value);
            }
        }
    }
    else if(requestType == "input") {
        vector<int> inputContent = notificationBox.stringToVectorInt(request[2], -100, 100);
        if(notificationBox.notificationText == "Valid") {
            vectorIntInitialize(inputContent);
        }
    }
    if(notificationBox.notificationText == "Valid") {
        notificationBox.notificationText.clear();
    }
    return true;
}

void DS1::vectorIntInitialize(vector<int>& vi) {
    doublyLinkedList->build(vi);
}

bool DS1::operateInsert(vector<string>& request, int stepRequest, string& explanationText) {
    if(taskManagement.doneTask() && stepRequest != PDSAnimation::goBackward && stepRequest != PDSAnimation::skipBackward) {
        return true;
    }
    bool done = true;
    string requestType = request[1];
    if(requestType == "head") {
        int value = notificationBox.getOneNum(request[2], -100, 100);
        if(notificationBox.notificationText == "Valid") {
            int codeLine = -1;
            done = animationManagement.insertHead(value, stepRequest, explanationText, codeLine);
            vector<string> codes = {
                "tmp = new Node(x)", // line 0
                "if head == nullptr:", // line 1
                "    head = tmp", // line 2
                "    tail = tmp", // line 3
                "else:", // line 4
                "    tmp->pNext = head", // line 5
                "    head->pPrev = tmp", // line 6
                "    head = tmp", // line 7
            };
            pseudoCode.setPseudoCode(codes, codes.size());
            pseudoCode.update(codeLine);
        }
        doublyLinkedList = animationManagement.dataStructurePointer;
    }
    else if(requestType == "tail") {
        int value = notificationBox.getOneNum(request[2], -100, 100);
        if(notificationBox.notificationText == "Valid") {
            int codeLine = -1;
            done = animationManagement.insertTail(value, stepRequest, explanationText, codeLine);
            vector<string> codes = {
                "tmp = new Node(x)", // line 0
                "if head == nullptr:", // line 1
                "    head = tmp", // line 2
                "    tail = tmp", // line 3
                "else:", // line 4
                "    tail->pNext = tmp", // line 5
                "    tmp->pPrev = tail", // line 6
                "    tail = tmp", // line 7
            };
            pseudoCode.setPseudoCode(codes, codes.size());
            pseudoCode.update(codeLine);
        }
        doublyLinkedList = animationManagement.dataStructurePointer;
    }
    else if(requestType == "after") {
        int position = notificationBox.getOneNum(request[2], 0, 99);
        if(notificationBox.notificationText != "Valid") {
            return true;
        }
        int value = notificationBox.getOneNum(request[3], -100, 100);
        if(notificationBox.notificationText == "Valid") {
            int codeLine = -1;
            done = animationManagement.insertAfter(position, value, stepRequest, explanationText, codeLine);
            vector<string> codes0 = {
                "prev = head", // line 0
                "for i = 0; i < position && prev != nullptr; i++", // line 1
                "    prev = prev->pNext", // line 2
            };
            vector<string> codes1 = {
                "if prev != nullptr:", // line 3
                "    tmp = new Node(x)", // line 4
                "    tmp->pNext = prev->pNext", // line 5
                "    prev->pNext = tmp", // line 6
                "    tmp->pPrev = prev", // line 7
                "    if tmp->pNext != nullptr:", // line 8
                "        tmp->pNext->pPrev = tmp", // line 9
                "    if prev == tail:", // line 10
                "        tail = tmp", // line 11
            };
            if(codeLine <= 2) {
                pseudoCode.setPseudoCode(codes0, codes0.size());
                pseudoCode.update(codeLine);
            }
            else {
                pseudoCode.setPseudoCode(codes1, codes1.size());
                pseudoCode.update(codeLine - 3);
            }
        }
        doublyLinkedList = animationManagement.dataStructurePointer;
    }
    if(notificationBox.notificationText == "Valid") {
        notificationBox.notificationText.clear();
    }
    return done;
}

bool DS1::operateRemove(vector<string>& request, int stepRequest, string& explanationText) {
    if(taskManagement.doneTask() && stepRequest != PDSAnimation::goBackward && stepRequest != PDSAnimation::skipBackward) {
        return true;
    }
    bool done = true;
    int value = notificationBox.getOneNum(request[1], 0, 99);
    if(notificationBox.notificationText == "Valid") {
        done = animationManagement.remove(value, stepRequest, explanationText);
        doublyLinkedList = animationManagement.dataStructurePointer;
        notificationBox.notificationText.clear();
    }
    return done;
}

bool DS1::operateSearch(vector<string>& request, int stepRequest, string& explanationText) {
    if(taskManagement.doneTask() && stepRequest != PDSAnimation::goBackward && stepRequest != PDSAnimation::skipBackward) {
        return true;
    }
    bool done = true;
    int value = notificationBox.getOneNum(request[1], -100, 100);
    if(notificationBox.notificationText == "Valid") {
        done = animationManagement.search(value, stepRequest, explanationText);
        doublyLinkedList = animationManagement.dataStructurePointer;
        notificationBox.notificationText.clear();
    }
    return done;
}

bool DS1::operateUpdate(PNode* chosen, vector<string>& request, int stepRequest, string& explanationText) {
    if(taskManagement.doneTask() && stepRequest != PDSAnimation::goBackward && stepRequest != PDSAnimation::skipBackward) {
        return true;
    }
    bool done = true;
    int value = notificationBox.getOneNum(request[1], 0, 99);
    chosen->highlight = true;
    chosen->setInformationState(DoublyLinkedList::Chosen, true);
    if(notificationBox.notificationText == "Valid") {
        done = animationManagement.update(chosen, value, stepRequest, explanationText);
        doublyLinkedList = animationManagement.dataStructurePointer;
        notificationBox.notificationText.clear();
    }
    if(done) {
        chosen->highlight = false;
        chosen->setInformationState(DoublyLinkedList::Chosen, false);
    }
    return done;
}