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
    LInputBox inputBox;
    LFunctionArea functionArea;
    AVL Tree;
    bool isAnimation;
    DS3();
    void draw();
    void RandomInitialize();
    void Insert();
    void Delete();
};