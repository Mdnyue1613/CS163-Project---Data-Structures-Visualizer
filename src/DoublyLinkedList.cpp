#include "../header/DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList(void) {
    n = 0;
    head = tail = nullptr;
    inAnimation = false;
}

DoublyLinkedList::~DoublyLinkedList(void) {
    removeAll();
}

void DoublyLinkedList::update(void) {
    updateDataStructure();
    updateAnimation();
}

void DoublyLinkedList::updateDataStructure(void) {
    PNode* tmp = head;
    while(tmp != nullptr) {
        tmp->update();
        tmp = tmp->pNext;
    }
}

void DoublyLinkedList::updateAnimation(void) {
    
}

void DoublyLinkedList::draw(void) {
    drawDataStructure();
    drawHeadAndTailText();
    drawAnimation();
}

void DoublyLinkedList::drawDataStructure(void) {
    PNode* tmp = head;
    while(tmp) {
        tmp->drawLine();
        tmp = tmp->pNext;
    }
    tmp = head;
    while(tmp) {
        tmp->drawNode();
        tmp = tmp->pNext;
    }
}

void DoublyLinkedList::drawHeadAndTailText(void) {
    // Empty list
    if(head == nullptr)
        return;

    const float textSize = PConstants::PNode::informationSize;
    const float radius = PConstants::PNode::outerRadius;
    const float space = PConstants::PNode::textSpace;
    
    // The list has one element
    if(head == tail) {
        string content = "head/tail";
        float contentWidth = MeasureText(content.c_str(), textSize);

        DrawText(content.c_str(), head->centerFrom.x - contentWidth / 2.f, head->centerFrom.y + radius + space, textSize, BLACK);
    }
    // The list has more than one
    else {
        string contentHead = "head";
        string contentTail = "tail";
        float contentHeadWidth = MeasureText(contentHead.c_str(), textSize);
        float contentTailWidth = MeasureText(contentTail.c_str(), textSize);

        DrawText(contentHead.c_str(), head->centerFrom.x - contentHeadWidth / 2.f, head->centerFrom.y + radius + space, textSize, BLACK);
        DrawText(contentTail.c_str(), tail->centerFrom.x - contentTailWidth / 2.f, tail->centerFrom.y + radius + space, textSize, BLACK);
    }
}

void DoublyLinkedList::drawAnimation(void) {
    
}

void DoublyLinkedList::randomInitializer(int n) {
    PRandom dist;
    
    if(head)
        removeAll();

    for(int i = 0; i < n; i++) {
        insertTail(dist.random(1, 30));
    }
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
    if(head == nullptr) {
        head = new PNode(x, nullptr, nullptr);
        tail = head;
    }
    else {
        head->pPrev = new PNode(x, nullptr, head);
        head = head->pPrev;
    }
    // Shift positions
    PNode* tmp = head;
    while(tmp != nullptr) {
        tmp->makePosition(false);
        tmp = tmp->pNext;
    }
}

void DoublyLinkedList::insertTail(int x) {
    n++;
    if(head == nullptr) {
        head = new PNode(x, nullptr, nullptr);
        tail = head;
    }
    else {
        tail->pNext = new PNode(x, tail, nullptr);
        tail = tail->pNext;
    }
}

void DoublyLinkedList::insertAfter(int p, int x) {
    // Unvalid format: List is empty
    if(head == nullptr) {
        return;
    }
    
    // Unvalid format: p exceeds number of nodes
    if(p >= n) {
        return;
    }

    n++;

    // Find indicated position
    PNode* pre = head;
    for(int i = 0; i < p; i++)
        pre = pre->pNext;

    PNode* nxt = pre->pNext;
    PNode* add = new PNode(x, pre, nxt);
    pre->pNext = add;
    if(nxt != nullptr)
        nxt->pPrev = add;

    // Shift positions
    reloadPositions();
}

void DoublyLinkedList::build(vector<int>& vi) {
    removeAll();
    for(int i = 0; i < (int)vi.size(); i++) {
        insertTail(vi[i]);
    }
}

PNode* DoublyLinkedList::getIthNode(int n) {
    PNode* tmp = head;
    for(int i = 1; i <= n; i++) {
        if(tmp == nullptr) 
            return nullptr;
        tmp = tmp->pNext;
    }
    return tmp;
}

void DoublyLinkedList::reloadPositions(void) {
    PNode* tmp = head;
    while(tmp != nullptr) {
        tmp->makePosition(false);
        tmp = tmp->pNext;
    }
}

void DoublyLinkedList::addNodeHead(int value) {
    // I. Create a new node
    PNode* newNode = new PNode(value, nullptr, nullptr);

    // II. Set position above the indicated position
    if(head == nullptr) {
        head = tail = newNode;
    }
    else {
        head->pPrev = newNode;
        newNode->pNext = head;
        head = newNode;
    }

    reloadPositions();
}

void DoublyLinkedList::highlightNode(int i) {
    PNode* tmp = getIthNode(i);
    if(tmp == nullptr) return;
    tmp->highlight = true;
}

void DoublyLinkedList::unHighlightNode(int i) {
    PNode* tmp = getIthNode(i);
    if(tmp == nullptr) return;
    tmp->highlight = false;
}

void DoublyLinkedList::displayLinkNext(int i) {
    PNode* cur = getIthNode(i);
    if(cur == nullptr) 
        return;
    cur->addLineState(PNode::NextOnly);
}

void DoublyLinkedList::displayLinkPrev(int i) {
    PNode* cur = getIthNode(i);
    if(cur == nullptr) 
        return;
    cur->addLineState(PNode::PrevOnly);
}

void DoublyLinkedList::setDisplayLine(int i, int state) {
    PNode* tmp = getIthNode(i);
    if(tmp == nullptr)
        return;
    tmp->setLineState(state);
}