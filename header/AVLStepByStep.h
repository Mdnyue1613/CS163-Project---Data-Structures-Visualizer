#pragma once
#include "AVL.h"

struct AVLStepByStep{
    vector<AVL> AVLState;
    AVL * dataStructure;
    void build(void) {
        AVLState = dataStructure->insertAnimation();
    }
    void update(void) {
        *dataStructure = AVLState.back();
    }
};