#pragma once
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cstring>
#include "PNodeLine.h"
#include "PRandom.h"
#include "PConstants.h"
using namespace std;

struct PNode {
    // Data
    int data;
    PNode *pNext, *pPrev;

    // Position
    Vector2 centerFrom, center; // Centers of the circle

    // Line
    PNodeLine lPrev, lNext;

    // Direction
    int direction;

    // Content
    char label[5];
    int labelLength;

    // Information
    const string informationName[4] = { "head", "tail", "tmp", "prev" };
    bool informationState[4] = {false, false, false, false};
    string information;

    // Hightlight
    bool highlight;

    // Update
    bool updatedPosition;

    // Initialize
    PNode(void);
    PNode(int data);
    void makeLabel(void); // initialize the label of the node
    void makePosition(void); // initialie the position of the node

    // Update
    void update(void); // update node's attributes
    bool updatePosition(void); // update node's position, return true if the progress is completed
    void updateLine(void); // update line connecting with the previous node (if exists): arrowHeadStart1, arrowHeadStart2, arrowHeadStart3, arrowHeadEnd1, arrowHeadEnd2, arrowHead3
    void quickUpdate(void); // skip animation

    // Draw
    void drawLine(void); // draw line (if exists)
    void drawNode(void); // draw node and content
    void drawText(void); // draw a text informing the node below the node

    // Set
    void setPosition(Vector2 pos); // move to pos
    void setHighlight(bool on); // set the highlight state
    void setHighlightPrevLink(bool on); // set the highlight state of the previous link
    void setHighlightNextLink(bool on); // set the highlight state of the next link

    // Information
    void setInformation(string information); // set information
    void setInformationState(int i, bool on); // set information state
    void resetInformationState(void); // reset information type

    // Get
    bool positionIsUpdated(void);
};