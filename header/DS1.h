#pragma once
#include "raylib.h"
#include "PTitleBox.h"
#include "PFunctionArea.h"
#include "DoublyLinkedList.h"
#include "PConstants.h"
#include "PRandom.h"
#include <string>
#include <vector>
#include <random>
using namespace std;

struct DS1 {
    PTitleBox titleBox;
    PFunctionArea functionArea;
    DoublyLinkedList doublyLinkedList;
    PRandom randomGenerator;

    DS1(void); // initialize
    void draw(void); // draw
    void operateInitialize(vector<string>& request);
    void randomInitialize(int x); // initialize a random data
    vector<int> stringToVectorInt(string& s);
    void vectorIntInitialize(vector<int>& vi);
};