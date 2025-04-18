#include "../header/AVL.h"

void AVLAnimation::reset(void) {
    recordVersionStack.clear();
    recordIntStack.clear();
    recordBoolStack.clear();
    recordStringStack.clear();
    recordVectorColorStack.clear();
    recordColorStack.clear();
    recordFloatStack.clear();
    recordTreeNodePointerStack.clear();
    recordTreeNodePointerVectorStack.clear();
    recordVector2Stack.clear();
    recordCreateNodeStack.clear();
    recordTreeNodeRecursionStack.clear();
    recordVectorBoolStack.clear();
}

void AVLAnimation::recordVersion(void) {
    recordVersionStack.push_back("Begin");
}
void AVLAnimation::recordInt(int *p) {
    recordVersionStack.push_back("int");
    recordIntStack.push_back({p, *p});
}
void AVLAnimation::recordBool(bool *p) {
    recordVersionStack.push_back("bool");
    recordBoolStack.push_back({p, *p});
}
void AVLAnimation::recordString(string *p) {
    recordVersionStack.push_back("string");
    recordStringStack.push_back({p, *p});
}
void AVLAnimation::recordVectorColor(vector<Color> *p) {
    recordVersionStack.push_back("vector<Color>");
    recordVectorColorStack.push_back({p, *p});
}
void AVLAnimation::recordColor(Color *p) {
    recordVersionStack.push_back("Color");
    recordColorStack.push_back({p, *p});
}
void AVLAnimation::recordFloat(float *p) {
    recordVersionStack.push_back("float");
    recordFloatStack.push_back({p, *p});
}
void AVLAnimation::recordTreeNodePointer(TreeNode **p) {
    recordVersionStack.push_back("TreeNode*");
    recordTreeNodePointerStack.push_back({p, *p});
}
void AVLAnimation::recordTreeNodePointerVector(vector<TreeNode*> *p) {
    recordVersionStack.push_back("vector<TreeNode*>");
    if(p->size() == 0)
        recordTreeNodePointerVectorStack.push_back({p, vector<TreeNode*>{}});
    else 
        recordTreeNodePointerVectorStack.push_back({p, *p});
}
void AVLAnimation::recordVector2(Vector2 *p) {
    recordVersionStack.push_back("Vector2");
    recordVector2Stack.push_back({p, *p});
}
void AVLAnimation::recordCreateNode(TreeNode **p) {
    recordVersionStack.push_back("CreateNode");
    recordCreateNodeStack.push_back(p);
}
void AVLAnimation::recordTreeNodeRecursion(vector<TreeNode**> *p) {
    recordVersionStack.push_back("TreeNodeRecursionStack");
    recordTreeNodeRecursionStack.push_back({p, *p});
}
void AVLAnimation::recordVectorBool(vector<bool> *p) {
    recordVersionStack.push_back("vector<bool>");
    recordVectorBoolStack.push_back({p, *p});
}

bool AVLAnimation::undoVersion(int stepRequest) {
    if(recordVersionStack.size() == 0) {
        cerr << "Error: AVLAnimation::undoVersion().";
        exit(1);
    }
    int cntBegin = 0;
    while(true) {
        string top = recordVersionStack.back();
        cntBegin += (top == "Begin");
        if(top == "Begin" && stepRequest == AVLAnimation::requestID::goBackward && cntBegin == 2) {
            break;
        }
        if(stepRequest == AVLAnimation::requestID::skipBackward && (int)recordVersionStack.size() == 1) {
            break;
        }
        recordVersionStack.pop_back();
        if(top == "int") {
            undoInt();
        } else if(top == "bool") {
            undoBool();
        } else if(top == "string") {
            undoString();
        } else if(top == "vector<Color>") {
            undoVectorColor();
        } else if(top == "Color") {
            undoColor();
        } else if(top == "float") {
            undoFloat();
        } else if(top == "TreeNode*") {
            undoTreeNodePointer();
        } else if(top == "vector<TreeNode*>") {
            undoTreeNodePointerVector();
        } else if(top == "Vector2") {
            undoVector2();
        } else if(top == "CreateNode") {
            undoCreateNode();
        } else if(top == "TreeNodeRecursionStack") {
            undoTreeNodeRecursion();
        } else if(top == "vector<bool>") {
            undoVectorBool();
        } else {
            cerr << "Error: AVLAnimation::undoVersion().";
            exit(1);
        }
    }
    return false;
}
void AVLAnimation::undoInt(void) {
    if(recordIntStack.size() == 0) {
        cerr << "Error: AVLAnimation::undoInt().";
        exit(1);
    }
    *recordIntStack.back().first = recordIntStack.back().second;
    recordIntStack.pop_back();
}
void AVLAnimation::undoBool(void) {
    if(recordBoolStack.size() == 0) {
        cerr << "Error: AVLAnimation::undoBool().";
        exit(1);
    }
    *recordBoolStack.back().first = recordBoolStack.back().second;
    recordBoolStack.pop_back();
}
void AVLAnimation::undoString(void) {
    if(recordStringStack.size() == 0) {
        cerr << "Error: AVLAnimation::undoString().";
        exit(1);
    }
    *recordStringStack.back().first = recordStringStack.back().second;
    recordStringStack.pop_back();
}
void AVLAnimation::undoVectorColor(void) {
    if(recordVectorColorStack.size() == 0) {
        cerr << "Error: AVLAnimation::undoVectorColor().";
        exit(1);
    }
    *recordVectorColorStack.back().first = recordVectorColorStack.back().second;
    recordVectorColorStack.pop_back();
}
void AVLAnimation::undoColor(void) {
    if(recordColorStack.size() == 0) {
        cerr << "Error: AVLAnimation::undoColor().";
        exit(1);
    }
    *recordColorStack.back().first = recordColorStack.back().second;
    recordColorStack.pop_back();
}
void AVLAnimation::undoFloat(void) {
    if(recordFloatStack.size() == 0) {
        cerr << "Error: AVLAnimation::undoFloat().";
        exit(1);
    }
    *recordFloatStack.back().first = recordFloatStack.back().second;
    recordFloatStack.pop_back();
}
void AVLAnimation::undoTreeNodePointer(void) {
    if(recordTreeNodePointerStack.size() == 0) {
        cerr << "Error: AVLAnimation::undoTreeNodePointer().";
        exit(1);
    }
    *recordTreeNodePointerStack.back().first = recordTreeNodePointerStack.back().second;
    recordTreeNodePointerStack.pop_back();
}
void AVLAnimation::undoTreeNodePointerVector(void) {
    if(recordTreeNodePointerVectorStack.size() == 0) {
        cerr << "Error: AVLAnimation::undoTreeNodePointerVector().";
        exit(1);
    }
    *recordTreeNodePointerVectorStack.back().first = recordTreeNodePointerVectorStack.back().second;
    recordTreeNodePointerVectorStack.pop_back();
}
void AVLAnimation::undoVector2(void) {
    if(recordVector2Stack.size() == 0) {
        cerr << "Error: AVLAnimation::undoVector2().";
        exit(1);
    }
    *recordVector2Stack.back().first = recordVector2Stack.back().second;
    recordVector2Stack.pop_back();
}
void AVLAnimation::undoCreateNode(void) {
    if(recordCreateNodeStack.size() == 0) {
        cerr << "Error: AVLAnimation::undoCreateNode().";
        exit(1);
    }
    delete *recordCreateNodeStack.back();
    *recordCreateNodeStack.back() = nullptr;
    recordCreateNodeStack.pop_back();
}
void AVLAnimation::undoTreeNodeRecursion(void) {
    if(recordTreeNodeRecursionStack.size() == 0) {
        cerr << "Error: AVLAnimation::undoTreeNodeRecursion().";
        exit(1);
    }
    *recordTreeNodeRecursionStack.back().first = recordTreeNodeRecursionStack.back().second;
    recordTreeNodeRecursionStack.pop_back();
}
void AVLAnimation::undoVectorBool(void) {
    if(recordVectorBoolStack.size() == 0) {
        cerr << "Error: AVLAnimation::undoVectorBool().";
        exit(1);
    }
    *recordVectorBoolStack.back().first = recordVectorBoolStack.back().second;
    recordVectorBoolStack.pop_back();
}