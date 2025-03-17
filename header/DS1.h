#pragma once
#include "raylib.h"
#include "PTitleBox.h"
#include "PFunctionArea.h"
#include "DoublyLinkedList.h"
#include <string>
#include <vector>
#include <random>
using namespace std;

struct DS1 {
    PTitleBox titleBox;
    PFunctionArea functionArea;
    DoublyLinkedList doublyLinkedList;

    DS1(void); // initialize
    void draw(void); // draw
    void randomInitialize(void); // initialize a random data
};