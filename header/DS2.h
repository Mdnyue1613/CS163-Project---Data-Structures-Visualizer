#pragma once
#include "raylib.h"
#include "PTitleBox.h"
#include "DFunctionArea.h"
#include "Hashtable.h"
#include "PConstants.h"
#include "PRandom.h"
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

    string statusMessage;
    float statusMessageTimer;
    
    DS2(void); // initialize
    ~DS2(void); // destructor
    void draw(void); // draw
    void operateInitialize(vector<string>& request);
    void operateInsert(int &value);
    void randomInitialize(int x); // initialize a random data
    vector<int> stringToVectorInt(string& s);
    void vectorIntInitialize(vector<int>& vi);
    void loadTextures(void);
    void prepare(void);
    void update (void);
    //notification for errors
    void setStatusMessage(const string& msg, float duration = 3.0f);
};