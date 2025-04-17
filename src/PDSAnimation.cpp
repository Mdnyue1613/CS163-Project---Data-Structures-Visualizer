#include "../header/PDSAnimation.h"

PDSAnimation::PDSAnimation(void) : 
    dataStructurePointer(nullptr), 
    taskManagementPointer(nullptr),
    waitRequest(true) {}

PDSAnimation::PDSAnimation(DoublyLinkedList * dataStructurePointer, PTaskManagement * taskManagementPointer) : 
    dataStructurePointer(dataStructurePointer), 
    taskManagementPointer(taskManagementPointer),
    waitRequest(true) {}

void PDSAnimation::reset(void) {
    while(undoStack.size() > 0) {
        undoStack.pop();
    }
    while(undoBoolStack.size() > 0) {
        undoBoolStack.pop();
    }
    while(undoPNodePointerStack.size() > 0) {
        undoPNodePointerStack.pop();
    }
    while(undoPNodePointerStack2.size() > 0) {
        undoPNodePointerStack2.pop();
    }
    while(undoIntStack.size() > 0) {
        undoIntStack.pop();
    }
    while(undoFloatStack.size() > 0) {
        undoFloatStack.pop();
    }
    while(undoVectorBoolStack.size() > 0) {
        undoVectorBoolStack.pop();
    }
    while(undoDeletePNodePointerStack.size() > 0) {
        undoDeletePNodePointerStack.pop();
    }
    while(undoVector2Stack.size() > 0) {
        undoVector2Stack.pop();
    }
}

void PDSAnimation::makeVersion(void) {
    undoStack.push("Begin");
}

void PDSAnimation::recordBool(bool * p) {
    undoStack.push("bool");
    undoBoolStack.push({p, *p});
}
void PDSAnimation::recordPNodePointer(PNode * * p, bool remove = false) {
    undoStack.push("PNode*");
    undoPNodePointerStack.push({{p, *p}, remove});
}
void PDSAnimation::recordPNodePointer2(PNode * * p, PNode * * p2) {
    undoStack.push("PNode* PNode*");
    undoPNodePointerStack2.push({p, p2});
}
void PDSAnimation::recordDeletePNodePointer(PNode * * p) {
    undoStack.push("delete PNode*");
    undoDeletePNodePointerStack.push({p, **p});
}
void PDSAnimation::recordInt(int * p) {
    undoStack.push("int");
    undoIntStack.push({p, *p});
}
void PDSAnimation::recordFloat(float * p) {
    undoStack.push("float");
    undoFloatStack.push({p, *p});
}
void PDSAnimation::recordVectorBool(vector<bool> * p) {
    undoStack.push("vector<bool>");
    undoVectorBoolStack.push({p, *p});
}
void PDSAnimation::recordVector2(Vector2 * p) {
    undoStack.push("Vector2");
    undoVector2Stack.push({p, *p});
}

bool PDSAnimation::undoVersion(int stepRequest) {
    int cntBegin = 0;
    while(true) {
        if(undoStack.empty()) {
            cerr << "Error: PDSAnimation::undoVersion()\n";
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
        else if(top == "PNode*") {
            undoPNodePointer();
        }
        else if(top == "PNode* PNode*") {
            undoPNodePointer2();
        }
        else if(top == "delete PNode*") {
            undoDeletePNodePointer();
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
        else if(top == "Vector2") {
            undoVector2();
        }
    }
    return false;
}
void PDSAnimation::undoBool(void) {
    if(undoBoolStack.empty()) {
        cerr << "Error: PDSAnimation::undoBool().\n";
        exit(1);
    }
    *undoBoolStack.top().first = undoBoolStack.top().second;
    undoBoolStack.pop();
}
void PDSAnimation::undoPNodePointer(void) {
    if(undoPNodePointerStack.empty()) {
        cerr << "Error: PDSAnimation::undoPNodePointer().\n";
        exit(1);
    }
    bool remove = undoPNodePointerStack.top().second;
    if(remove) {
        delete *undoPNodePointerStack.top().first.first;
    }
    *undoPNodePointerStack.top().first.first = undoPNodePointerStack.top().first.second;
    undoPNodePointerStack.pop();
}
void PDSAnimation::undoPNodePointer2(void) {
    if(undoPNodePointerStack2.empty()) {
        cerr << "Error: PDSAnimation::undoPNodePointer2().\n";
        exit(1);
    }
    *undoPNodePointerStack2.top().first = *undoPNodePointerStack2.top().second;
    undoPNodePointerStack2.pop();
}
void PDSAnimation::undoDeletePNodePointer(void) {
    if(undoDeletePNodePointerStack.empty()) {
        cerr << "Error: PDSAnimation::undoDeletePNodePointer().\n";
        exit(1);
    }
    *undoDeletePNodePointerStack.top().first = new PNode(undoDeletePNodePointerStack.top().second);
    undoDeletePNodePointerStack.pop();
}
void PDSAnimation::undoInt(void) {
    if(undoIntStack.empty()) {
        cerr << "Error: PDSAnimation::undoInt().\n";
        exit(1);
    }
    *undoIntStack.top().first = undoIntStack.top().second;
    undoIntStack.pop();
}
void PDSAnimation::undoFloat(void) {
    if(undoFloatStack.empty()) {
        cerr << "Error: PDSAnimation::undoFloat().\n";
        exit(1);
    }
    *undoFloatStack.top().first = undoFloatStack.top().second;
    undoFloatStack.pop();
}
void PDSAnimation::undoVectorBool(void) {
    if(undoVectorBoolStack.empty()) {
        cerr << "Error: PDSAnimation::undoVectorBool().\n";
        exit(1);
    }
    *undoVectorBoolStack.top().first = undoVectorBoolStack.top().second;
    undoVectorBoolStack.pop();
}
void PDSAnimation::undoVector2(void) {
    if(undoVector2Stack.empty()) {
        cerr << "Error: PDSAnimation::undoVector2().\n";
        exit(1);
    }
    *undoVector2Stack.top().first = undoVector2Stack.top().second;
    undoVector2Stack.pop();
}