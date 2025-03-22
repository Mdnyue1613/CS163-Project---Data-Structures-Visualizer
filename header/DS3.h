#pragma once
#include "PTitleBox.h"
#include "AVL.h"
#include "PInitializeMenu.h"
#include "PFunctionArea.h"
#include "Constants.h"

struct DS3 {
    PTitleBox titleBox;
    PFunctionArea functionArea;
    AVL Tree;

    DS3();
    void draw();
    void RandomInitialize();
};