#include "../header/DoublyLinkedList.h"

DoublyLinkedList::Node::Node(void) {
    pNext = pPrev = nullptr;
}

void DoublyLinkedList::Node::draw(void) {
    DrawRing(center, innerRadius, outerRadius, 0, 360, 64, BLACK);
    DrawText(label, center.x - MeasureText(label, characterSize) / 2, 
        center.y - characterSize / 2, characterSize, BLACK);
    if(pPrev) {
        DrawLineEx(arrowStart, arrowEnd, lineThickness, BLACK);
        DrawTriangle(arrowHeadStart1, arrowHeadStart2, arrowHeadStart3, BLACK);
        DrawTriangle(arrowHeadEnd1, arrowHeadEnd2, arrowHeadEnd3, BLACK);
    }
}

void DoublyLinkedList::Node::makeLabel(void) {
    labelLength = 0;
    int x = data;
    do {
        label[labelLength++] = char(x % 10 + '0');
        x /= 10;
    } while(x > 0);
    for(int i = 0; i < labelLength / 2; i++)
        swap(label[i], label[labelLength - 1 - i]);
    label[labelLength] = '\0';
}

void DoublyLinkedList::Node::makeNodeAndLine(void) {
    // Direction: Rightward
    if(pPrev->direction == 1 && pPrev->center.x + 100 + outerRadius < GetScreenWidth()) {
        direction = 1;
        center = {pPrev->center.x + 100, pPrev->center.y};
        arrowStart = {pPrev->center.x + pPrev->outerRadius, pPrev->center.y};
        arrowEnd = {center.x - outerRadius, center.y};
        arrowHeadStart1 = arrowStart;
        arrowHeadStart2 = {arrowStart.x + arrowWidth, arrowStart.y + arrowHeight};
        arrowHeadStart3 = {arrowStart.x + arrowWidth, arrowStart.y - arrowHeight};
        arrowHeadEnd1 = arrowEnd;
        arrowHeadEnd2 = {arrowEnd.x - arrowWidth, arrowEnd.y - arrowHeight};
        arrowHeadEnd3 = {arrowEnd.x - arrowWidth, arrowEnd.y + arrowHeight}; 
    }
    // Direction: Leftward
    else if(pPrev->direction == -1 && pPrev->center.x - 100 - outerRadius > 310) {
        direction = -1;
        center = {pPrev->center.x - 100, pPrev->center.y};
        arrowStart = {pPrev->center.x - pPrev->outerRadius, pPrev->center.y};
        arrowEnd = {center.x + outerRadius, center.y};
        arrowHeadStart1 = arrowStart;
        arrowHeadStart2 = {arrowStart.x - arrowWidth, arrowStart.y - arrowHeight};
        arrowHeadStart3 = {arrowStart.x - arrowWidth, arrowStart.y + arrowHeight};
        arrowHeadEnd1 = arrowEnd;
        arrowHeadEnd2 = {arrowEnd.x + arrowWidth, arrowEnd.y + arrowHeight};
        arrowHeadEnd3 = {arrowEnd.x + arrowWidth, arrowEnd.y - arrowHeight};
    }
    // Direction: Downward
    else {
        direction = -pPrev->direction;
        center = {pPrev->center.x, pPrev->center.y + 100};
        arrowStart = {pPrev->center.x, pPrev->center.y + pPrev->outerRadius};
        arrowEnd = {center.x, center.y - outerRadius};
        arrowHeadStart1 = arrowStart;
        arrowHeadStart2 = {arrowStart.x - arrowHeight, arrowStart.y + arrowWidth};
        arrowHeadStart3 = {arrowStart.x + arrowHeight, arrowStart.y + arrowWidth};
        arrowHeadEnd1 = arrowEnd;
        arrowHeadEnd2 = {arrowEnd.x + arrowHeight, arrowEnd.y - arrowWidth};
        arrowHeadEnd3 = {arrowEnd.x - arrowHeight, arrowEnd.y - arrowWidth}; 
    }
}

DoublyLinkedList::DoublyLinkedList(void) {
    head = tail = nullptr;
}

DoublyLinkedList::~DoublyLinkedList(void) {
    removeAll();
}

void DoublyLinkedList::draw(void) {
    Node* tmp = head;
    while(tmp) {
        tmp->draw();
        tmp = tmp->pNext;
    }
}
void DoublyLinkedList::random(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 30);
    
    if(head)
        removeAll();

    this->n = n;
    for(int i = 0; i < n; i++) {
        insert(dist(gen));
    }
}

void DoublyLinkedList::removeAll(void) {
    while(head) {
        Node* tmp = head;
        head = head->pNext;
        delete tmp;
    }
    head = tail = nullptr;
}

void DoublyLinkedList::insert(int x) {
    if(head == nullptr) {
        head = new Node;
        head->data = x;
        tail = head;
        head->direction = 1;
        head->center = {400, 200};
        head->makeLabel();
    }
    else {
        tail->pNext = new Node;
        tail->pNext->pPrev = tail;
        tail = tail->pNext;
        tail->data = x;
        tail->makeLabel();
        tail->makeNodeAndLine();
    }
}

void DoublyLinkedList::build(vector<int>& vi) {
    removeAll();
    n = vi.size();
    for(int i = 0; i < n; i++) {
        insert(vi[i]);
    }
}