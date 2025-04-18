#pragma once
#include "raylib.h"
#include "PTitleBox.h"
#include "DFunctionArea.h"
#include "Hashtable.h"
#include "PConstants.h"
#include "PRandom.h"
#include "PTaskManagement.h"
#include "PStepByStepMenu.h"
#include "DDSAnimation.h"
#include <string>
#include <vector>
#include <random>
using namespace std;

struct DS2 {
    PTitleBox titleBox;
    DFunctionArea functionArea;
    Hashtable hashtable;
    PRandom randomGenerator;
    Texture2D icon;
    PTaskManagement taskManagement;
    PStepByStepMenu stepByStepMenu;
    DDSAnimation animationManager;

    string statusMessage;
    float statusMessageTimer;
    
    DS2(void); // initialize
    ~DS2(void); // destructor
    void draw(void); // draw
    bool operateInitialize(vector<string>& request);
    bool operateInsert(vector<string>& request, int stepRequest, string& explanationText);
    bool operateRemove(vector<string>& request, int stepRequest, string& explanationText);
    bool operateSearch(vector<string>& request, int stepRequest, string& explanationText);
    void randomInitialize(int n, int m); // initialize a random data
    vector<int> stringToVectorInt(string& s);
    void vectorIntInitialize(vector<int>& vi);
    void loadTextures(void);
    void prepare(void);
    void update (void);
    //notification for errors
    void setStatusMessage(const string& msg, float duration = 3.0f);
};