#pragma once
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <random>
#include <algorithm>
#include <cstring>
#include "PConstants.h"
#include "PRandom.h"
#include "PNode.h"
using namespace std;

struct DoublyLinkedList {    
    // Data structure
    int n;
    PNode *head, *tail;

    // Constructor
    DoublyLinkedList(void);

    // Destructor
    ~DoublyLinkedList(void);

    // Update
    void update(void);
    void updateDataStructure(void);
    void updateAnimation(void);

    // Draw
    void draw(void); // draw all
    void drawDataStructure(void); // Draw data structures
    void drawHeadAndTailText(void); // Draw text indicating head and tail node
    void drawAnimation(void); // draw animations

    // Instantaneous functions
    void removeAll(void); // remove all nodes
        // Initializing functions
    void randomInitializer(int n); // randomize with number of nodes
    void build(vector<int>& vi); // build a linked list with given vector<int>
        // Inserting functions
    void insertHead(int x); // insert a new node at the head
    void insertTail(int x); // insert a new node at the tail
    void insertAfter(int p, int x); // insert a new node after node with index p (0-indexed)
    PNode* getIthNode(int i); // Get the pointer to the i-th node
    void reloadPositions(void);

    // Step-by-step functions
    bool inAnimation;

    void addNodeHead(int value); // Create a new node before the position-th node (0-indexed)
    void highlightNode(int i); // Highlight the i-th node
    void unHighlightNode(int i); // Unhighlight the i-th node
    void displayLinkNext(int i); // Display the node[i]->pNext link
    void displayLinkPrev(int i); // Display the node[i]->pPrev link
    void setDisplayLine(int i, int state); // Set line display state of the i-th node = state
};