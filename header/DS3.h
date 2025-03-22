#pragma once
#include "PTitleBox.h"
#include "AVL.h"
#include "PInitializeMenu.h"
#include "PFunctionArea.h"
#include "Constants.h"
#include "LInputBox.h"
#include "LFunctionArea.h"

struct DS3 {
    PTitleBox titleBox;
    LInputBox inputBox;
    LFunctionArea functionArea;
    AVL Tree;
    DS3();
    void draw();
    void RandomInitialize();
    void Insert();
};