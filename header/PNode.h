#pragma once
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cstring>
#include "PRandom.h"
#include "PConstants.h"
using namespace std;

struct PNode {
    // const int innerRadius = 26;
    // const int outerRadius = 30;
    // const int characterSize = 20;
    // const int lineThickness = 4;
    // const int arrowWidth = 6;
    // const int arrowHeight = 8;
    // Data
    int data;
    PNode *pNext, *pPrev;

    // Position
    Vector2 centerFrom, center; // Centers of the circle

    // Line
    enum lineStateID {
        NoDraw,
        NextOnly,
        PrevOnly,
        DrawAll
    };
    int lineState;
    Vector2 arrowHeadStart1, arrowHeadStart2, arrowHeadStart3; // Coordinates of the arrow head 1
    Vector2 arrowHeadEnd1, arrowHeadEnd2, arrowHeadEnd3; // Coordinates of the arrow head 2

    // Direction
    int direction;

    // Content
    char label[5];
    int labelLength;

    // Hightlight
    bool highlight;

    // Update
    bool updatedPosition;

    // Initialize
    PNode(void);
    PNode(int data, PNode *pPrev, PNode* pNext);
    void makeLabel(void); // initialize the label of the node
    void makePosition(bool isNew); // initialize the position of the node or shift after insertion

    // Update
    void update(void); // update node's attributes
    bool updatePosition(void); // update node's position, return true if the progress is completed
    void updateLine(void); // update line connecting with the previous node (if exists): arrowHeadStart1, arrowHeadStart2, arrowHeadStart3, arrowHeadEnd1, arrowHeadEnd2, arrowHead3

    // Draw
    void drawLine(void); // draw line (if exists)
    void drawNode(void); // draw node and content

    // Set
    void setPosition(Vector2 pos); // move to pos
    void setLineState(int state); // set line state
    void addLineState(int state); // add line state
};