#pragma once
#include "raylib.h"
#include "PTitleBox.h"
#include "PFunctionArea.h"
#include "DoublyLinkedList.h"
#include "PConstants.h"
#include "PRandom.h"
#include "PStepByStepMenu.h"
#include "PTaskManagement.h"
#include "PDSAnimation.h"
#include "PExplanationArea.h"
#include <string>
#include <vector>
#include <random>
#include <queue>
using namespace std;

struct DS1 {
    PTitleBox titleBox;
    PFunctionArea functionArea;
    PStepByStepMenu stepByStepMenu;
    DoublyLinkedList * doublyLinkedList;
    PRandom randomGenerator;
    PTaskManagement taskManagement;
    PDSAnimation animationManagement;
    PExplanationArea explanationArea;

    enum taskType {
        Initialize,
        Insert,
        Remove,
        Search,
        NoTask
    };

    DS1(void); // initialize
    ~DS1(void); // destructor

    void prepare(void); // prepare the areas

    // Update
    void update(void); // update

    // Draw
    void draw(void); // draw

    // Initialize mode functions
    bool operateInitialize(vector<string>& request, int stepRequest, string& explanationText); // Operate initializing request: return true when done
    vector<int> stringToVectorInt(string& s);
    void vectorIntInitialize(vector<int>& vi);

    // Insert mode functions
    bool operateInsert(vector<string>& request, int stepRequest, string& explanationText); // Operate inserting request: return true when done

    // Remove mode functions
    bool operateRemove(vector<string>& request, int stepRequest, string& explanationText); // Operate removing request: return true when done

    // Search mode functions
    bool operateSearch(vector<string>& request, int stepRequest, string& explanationText); // Operate searching request: return true when done
};