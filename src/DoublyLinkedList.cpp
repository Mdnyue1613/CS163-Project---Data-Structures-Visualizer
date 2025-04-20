#include "../header/DoublyLinkedList.h"
#include "../header/PConstants.h"

DoublyLinkedList::DoublyLinkedList(void) {
    // Data structure
    n = 0;
    head = tail = nullptr;
    // Animation
    // tmp
    animationTmp = nullptr;
    // prev
    animationPrev = nullptr;
    // chosen node
    animationChosen = nullptr;
    queryUpdate = nullptr;
    prevPosition = 0;
}

DoublyLinkedList::~DoublyLinkedList(void) {
    // Remove dynamic memory from linked list
    removeAll();

    // Remove dynamic memory from animation
    if(animationTmp != nullptr) {
        delete animationTmp;
    }
    if(animationPrev != nullptr) {
        delete animationPrev;
    }
}

void DoublyLinkedList::update(void) {
    // Update data structure before rendering
    updateDataStructure();

    // Update animation before rendering
    updateAnimation();

    // Update nodes' information text
    updateInformation();
}

void DoublyLinkedList::updateDataStructure(void) {
    PNode* tmp = head;
    while(tmp != nullptr) {
        tmp->update();
        if(tmp != animationChosen && CheckCollisionPointCircle(GetMousePosition(), tmp->centerFrom, PConstants::PNode::outerRadius) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            animationChosen = tmp;
        }
        else if(tmp == animationChosen && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            animationChosen = nullptr;
        }
        tmp = tmp->pNext;
    }
}

void DoublyLinkedList::updateAnimation(void) {
    if(animationTmp != nullptr) {
        animationTmp->update();
    }
    if(animationPrev != nullptr) {
        animationPrev->update();
    }
}

void DoublyLinkedList::updateInformation(void) {
    // Delete old information text
    PNode* tmp = head;
    while(tmp != nullptr) {
        tmp->resetInformationState();
        tmp = tmp->pNext;
    }
    if(animationTmp != nullptr) {
        animationTmp->resetInformationState();
    }
    if(animationPrev != nullptr) {
        animationPrev->resetInformationState();
    }
    if(animationChosen != nullptr) {
        animationChosen->resetInformationState();
    }
    // Update information text
    if(head != nullptr) {
        head->setInformationState(Head, true);
    }
    if(tail != nullptr) {
        tail->setInformationState(Tail, true);
    }
    if(animationTmp != nullptr) {
        animationTmp->setInformationState(Tmp, true);
    }
    if(animationPrev != nullptr) {
        animationPrev->setInformationState(Prev, true);
    }
    if(queryUpdate != nullptr) {
        queryUpdate->setInformationState(Chosen, true);
    }
}

void DoublyLinkedList::quickUpdateAnimation(void) {
    quickUpdateAnimationTmp();
}

void DoublyLinkedList::quickUpdateAnimationTmp(void) {
    animationTmp->quickUpdate();
}

void DoublyLinkedList::draw(void) {
    drawDataStructure();
    drawAnimation();
}

void DoublyLinkedList::drawDataStructure(void) {
    PNode* tmp = head;
    while(tmp) {
        tmp->drawLine();
        tmp = tmp->pNext;
    }
    tmp = head;
    if(animationChosen != nullptr) {
        animationChosen->highlight = true;
    }
    if(queryUpdate != nullptr) {
        queryUpdate->highlight = true;
    }
    while(tmp) {
        tmp->drawNode();
        tmp->drawText();
        tmp = tmp->pNext;
    }
    if(queryUpdate != nullptr) {
        queryUpdate->highlight = false;
    }
    if(animationChosen != nullptr) {
        animationChosen->highlight = false;
    }
}

void DoublyLinkedList::drawAnimation(void) {
    // Draw the tmp node
    drawAnimationTmp();
}

void DoublyLinkedList::drawAnimationTmp(void) {
    if(animationTmp == nullptr) 
        return;
    animationTmp->drawLine();
    animationTmp->drawNode();
    animationTmp->drawText();
}

int DoublyLinkedList::getNumNode(void) {
    return n;
}

void DoublyLinkedList::addNumNode(int x) {
    n += x;
}

void DoublyLinkedList::randomInitializer(int n) {
    PRandom dist;
    
    if(head)
        removeAll();

    for(int i = 0; i < n; i++) {
        insertTail(dist.random(1, 99));
    }

    // Shift to correct positions
    reloadPositions();
}

void DoublyLinkedList::removeAll(void) {
    n = 0;
    while(head != nullptr) {
        PNode* tmp = head;
        head = head->pNext;
        delete tmp;
    }
    head = tail = nullptr;
}

void DoublyLinkedList::insertHead(int x) {
    n++;
    PNode* tmp = new PNode(x);
    if(head == nullptr) {
        head = tmp;
        tail = tmp;
    }
    else {
        head->pPrev = tmp;
        tmp->pNext = head;
        head = tmp;
    }
    // Reload positions
    reloadPositions();
}

void DoublyLinkedList::insertTail(int x) {
    n++;
    PNode* tmp = new PNode(x);
    if(head == nullptr) {
        head = tmp;
        tail = tmp;
    }
    else {
        tail->pNext = tmp;
        tmp->pPrev = tail;
        tail = tmp;
    }
}

void DoublyLinkedList::insertAfter(int p, int x) {
    // Unvalid format: List is empty
    if(head == nullptr) {
        return;
    }

    // Find indicated position
    PNode* pre = getIthNode(p);

    // The p-th node does not exist
    if(pre == nullptr) {
        return;
    }

    n++;
    
    // Create the new node
    PNode* tmp = new PNode(x);
    // Declare the nxt node
    PNode* nxt = pre->pNext;
    
    // Make links
    tmp->pPrev = pre;
    pre->pNext = tmp;
    if(nxt != nullptr) tmp->pNext = nxt;
    if(nxt != nullptr) nxt->pPrev = tmp;
    if(pre == tail) tail = tmp;

    // Shift positions
    reloadPositions();
}

void DoublyLinkedList::build(vector<int>& vi) {
    removeAll();
    for(int i = 0; i < (int)vi.size(); i++) {
        insertTail(vi[i]);
    }

    // Shift positions
    reloadPositions();
}

PNode* DoublyLinkedList::getIthNode(int n) {
    PNode* tmp = head;
    for(int i = 0; i < n && tmp != nullptr; i++)
        tmp = tmp->pNext;
    return tmp;
}

void DoublyLinkedList::reloadPositions(void) {
    PNode* tmp = head;
    while(tmp != nullptr) {
        // Reloading position based on the linked list
        if(tmp == head) {
            tmp->setPosition(PConstants::DS1::headPosition);
        }
        else {
            nextNodePosition(tmp->pPrev, tmp);
        }

        // If there is an animationTmp node, shift the node 'tmp' forward
        if(animationTmp != nullptr && animationTmp != tmp && tmp->center == animationTmp->center) {
            nextNodePosition(animationTmp, tmp);
        }

        // Moving to the next node in the linked list
        tmp = tmp->pNext;
    }
}

void DoublyLinkedList::nextNodePosition(PNode *& node, PNode *& next) {
    const float outerRadius = PConstants::PNode::outerRadius;
    const float lineLength = PConstants::PNode::lineLength;
    const float screenWidth = 1200;
    const float distanceBetweenTwoCenter = 2.f * outerRadius + lineLength;
    const float distanceBetweenTwoCenterPlusARadius = distanceBetweenTwoCenter + outerRadius;
    const float functionAreaWidth = PConstants::PFunctionArea::size.x;
    // Next node go to the right
    if(node->direction == 1 && node->center.x + distanceBetweenTwoCenterPlusARadius < screenWidth) {
        next->direction = 1;
        next->setPosition(Vector2Add(node->center, {distanceBetweenTwoCenter, 0}));
    }
    // Next node go to the left
    else if(node->direction == -1 && node->center.x - distanceBetweenTwoCenterPlusARadius > functionAreaWidth) {
        next->direction = -1;
        next->setPosition(Vector2Subtract(node->center, {distanceBetweenTwoCenter, 0}));
    }
    // Next node go downward
    else {
        next->direction = - node->direction;
        next->setPosition(Vector2Add(node->center, {0, distanceBetweenTwoCenter}));
    }
}

bool DoublyLinkedList::createdHead(void) {
    return head != nullptr;
}

void DoublyLinkedList::setHighlightHead(bool on) {
    head->setHighlight(on);
}

void DoublyLinkedList::assignAnimationTmpToHead(void) {
    // head = tmp
    head = animationTmp;
}

void DoublyLinkedList::assignAnimationTmpToHeadPrev(void) {
    if(head != nullptr) {
        head->pPrev = animationTmp;
    }
    else {
        cerr << "Warning: DoublyLinkedList::assignAnimationTmpToHeadPrev(void).\n";
    }
}

void DoublyLinkedList::setHighlightHeadPrevLink(bool on) {
    head->setHighlightPrevLink(on);
}

void DoublyLinkedList::setHeadToNull(void) {
    head = nullptr;
}

void DoublyLinkedList::setHeadPrevLinkToNull(void) {
    head->pPrev = nullptr;
}

void DoublyLinkedList::assignAnimationTmpToTail(void) {
    // tail = tmp
    tail = animationTmp;
}

void DoublyLinkedList::assignAnimationTmpToTailNext(void) {
    if(tail != nullptr) {
        tail->pNext = animationTmp;
    }
    else {
        cerr << "Warning: DoublyLinkedList::assignAnimationTmpToTailNext(void).\n";
    }
}

void DoublyLinkedList::setHighlightTail(bool on) {
    tail->setHighlight(on);
}

void DoublyLinkedList::setHighlightTailNextLink(bool on) {
    tail->setHighlightNextLink(on);
}

void DoublyLinkedList::setTailToNull(void) {
    tail = nullptr;
}

bool DoublyLinkedList::createdAnimationTmp(void) {
    return animationTmp != nullptr;
}

bool DoublyLinkedList::animationTmpIsUpdated(void) {
    return animationTmp->positionIsUpdated();
}

void DoublyLinkedList::setHighlightAnimationTmp(bool on) {
    animationTmp->setHighlight(on);
}

void DoublyLinkedList::setAnimationTmpToNull(void) {
    animationTmp = nullptr;
}

void DoublyLinkedList::assignHeadToAnimationTmpNext(void) {
    animationTmp->pNext = head;
}

void DoublyLinkedList::setHighlightAnimationTmpNextLink(bool on) {
    animationTmp->setHighlightNextLink(on);
}

void DoublyLinkedList::assignTailToAnimationTmpPrev(void) {
    animationTmp->pPrev = tail;
}

void DoublyLinkedList::assignAnimationPrevToAnimationTmpPrev(void) {
    animationTmp->pPrev = animationPrev;
}

void DoublyLinkedList::setHighlightAnimationTmpPrevLink(bool on) {
    animationTmp->setHighlightPrevLink(on);
}

void DoublyLinkedList::assignAnimationPrevNextToAnimationTmpNext(void) {
    animationTmp->pNext = animationPrev->pNext;
}

void DoublyLinkedList::assignAnimationTmpToAnimationTmpNextPrev(void) {
    if(animationTmp->pNext != nullptr)
        animationTmp->pNext->pPrev = animationTmp;
}

void DoublyLinkedList::setHighlightAnimationTmpNextPrevLink(bool on) {
    if(animationTmp->pNext != nullptr)
        animationTmp->pNext->setHighlightPrevLink(on);
}

void DoublyLinkedList::deleteAnimationTmp(void) {
    delete animationTmp;
    animationTmp = nullptr;
    reloadPositions();
}

void DoublyLinkedList::setAnimationTmpNextLinkToNull(void) {
    animationTmp->pNext = nullptr;
}

void DoublyLinkedList::assignHeadToAnimationPrev(void) {
    animationPrev = head;
    prevPosition = 0;
}

bool DoublyLinkedList::traversePrevDone(int position) {
    if(animationPrev == nullptr || prevPosition >= position) {
        prevPosition = 0;
        return true;
    }
    return false;
}

void DoublyLinkedList::traversePrev(int position) {
    if(traversePrevDone(position) == false) {
        animationPrev = animationPrev->pNext;
        prevPosition++;
    }
}

void DoublyLinkedList::setHighlightAnimationPrev(bool on) {
    if(animationPrev != nullptr) {
        animationPrev->setHighlight(on);
    }
}

bool DoublyLinkedList::createdAnimationPrev(void) {
    return animationPrev != nullptr;
}

void DoublyLinkedList::setAnimationPrevToNull(void) {
    animationPrev = nullptr;
    prevPosition = -1;
}

void DoublyLinkedList::assignAnimationTmpToAnimationPrevNext(void) {
    animationPrev->pNext = animationTmp;
}

void DoublyLinkedList::setHighlightAnimationPrevNextLink(bool on) {
    animationPrev->setHighlightNextLink(on);
}

void DoublyLinkedList::setHighlightAnimationPrevPrevLink(bool on) {
    animationPrev->setHighlightPrevLink(on);
}

bool DoublyLinkedList::isAnimationPrevTail(void) {
    return animationPrev == tail;
}

void DoublyLinkedList::createANewNode(int x) {
    if(animationTmp != nullptr) 
                delete animationTmp;
    animationTmp = new PNode(x);
}

void DoublyLinkedList::createNodeBefore(int i, int x) {
    // Get the i-th node: tmp
    PNode* tmp = getIthNode(i);
    // Cannot found tmp
    if(tmp == nullptr) {
        // Head position
        if(i == 0) {
            // Create a new node
            createANewNode(x);
            // Set position to head's position
            animationTmp->setPosition(PConstants::DS1::headPosition);
        }
        // Input is not valid
        else {
            cerr << "DoublyLinkedList::createNodeBefore(i, x): Input is not valid.\n";
            return;
        }
    }
    // Found tmp
    else {
        // Create a new node at the i-th node's position
        createANewNode(x);
        // Set position to tmp's position
        animationTmp->setPosition(tmp->center);
        // Reload all positions
        reloadPositions();
    }
}

void DoublyLinkedList::createNodeAfter(int i, int x) {
    // Get the i-th node: tmp
    PNode* tmp = getIthNode(i);
    // Cannot found tmp
    if(tmp == nullptr) {
        // Head position
        if(i == -1) {
            // Create a new node
            createANewNode(x);
            // Set position to head's position
            animationTmp->setPosition(PConstants::DS1::headPosition);
        }
        // Input is not valid
        else {
            cerr << "DoublyLinkedList::createNodeAfter(i, x): Input is not valid.\n";
            return;
        }
    }
    // Found tmp
    else {
        // Create a new node at the i-th node's position
        createANewNode(x);
        // Set position after the tmp's position
        nextNodePosition(tmp, animationTmp);
        // Reload all positions
        reloadPositions();
    }
}