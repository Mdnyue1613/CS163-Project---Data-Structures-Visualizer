#pragma once
#include "PTitleBox.h"
#include "AVL.h"
#include "PInitializeMenu.h"
#include "PFunctionArea.h"
#include "PConstants.h"
#include "LInputBox.h"
#include "LFunctionArea.h"

struct DS3 {
    PTitleBox titleBox;
    LFunctionArea functionArea;
    AVL Tree;
    bool isAnimation;
    DS3();
    void draw();
    void RandomInitialize(string num);
    void Insert(string num);
    void Delete(string num);
    void prepare();
};