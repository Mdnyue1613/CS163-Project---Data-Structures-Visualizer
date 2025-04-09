#pragma once
#include "raylib.h"
#include "PTitleBox.h"
#include "PFunctionArea.h"
#include "Hashtable.h"
#include "PConstants.h"
#include "PRandom.h"
#include <string>
#include <vector>
#include <random>
using namespace std;

struct DS2 {
    PTitleBox titleBox;
    PFunctionArea functionArea;
    Hashtable hashtable;
    PRandom randomGenerator;
    Texture2D icon;

    DS2(void); // initialize
    ~DS2(void); // destructor
    void draw(void); // draw
    void operateInitialize(vector<string>& request);
    void randomInitialize(int x); // initialize a random data
    vector<int> stringToVectorInt(string& s);
    void vectorIntInitialize(vector<int>& vi);
    void loadTextures(void);
};