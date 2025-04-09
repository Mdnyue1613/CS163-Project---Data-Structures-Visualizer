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
    ~DS1(void); // destructor
    void draw(void); // draw
    void update(void);

    // Initialize mode functions
    void operateInitialize(vector<string>& request); // Operate initializing request
    void randomInitialize(int x); // initialize a random data
    vector<int> stringToVectorInt(string& s);
    void vectorIntInitialize(vector<int>& vi);

    // Insert mode functions
    void operateInsert(vector<string>& request); // Operate inserting request

    void prepare(void);
};