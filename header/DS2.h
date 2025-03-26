#pragma once
#include "raylib.h"
#include "PTitleBox.h"
#include "PFunctionArea.h"
#include <string>
#include <vector>
#include <random>
using namespace std;

struct DS2 {
    PTitleBox titleBox;
    PFunctionArea functionArea;
    //DRAW CHAINING HASH TABLE 
    
    DS2(void); // initialize
    void draw(void); // draw
    void randomInitialize(void); // initialize a random data
};