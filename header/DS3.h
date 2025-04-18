#pragma once
#include "PTitleBox.h"
#include "AVL.h"
#include "PInitializeMenu.h"
#include "PFunctionArea.h"
#include "PConstants.h"
#include "LInputBox.h"
#include "LFunctionArea.h"
#include "PStepByStepMenu.h"
#include "PTaskManagement.h"
#include "PNotification.h"
#include<sstream>

struct DS3 {
    PTitleBox titleBox;
    LFunctionArea functionArea;
    PStepByStepMenu stepByStepMenu;
    PTaskManagement taskManagement;
    PNotification notificationBox;
    
    AVL Tree;
    bool isAnimation;
    DS3();
    void draw();
    void RandomInitialize(string num);
    void vectorIntInitialize(vector<int> nums);
    bool Insert(vector<string>& request, int stepRequest); // Return true if the task is done
    void insertAnimation();
    void Delete(string num);
    void Find(string num);
    void prepare();
    vector<int> stringToVectorInt(string s);
    void updateSelectionNode();
};