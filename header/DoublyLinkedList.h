#pragma once
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <random>
#include <algorithm>
#include <cstring>
#include "PConstants.h"
#include "PRandom.h"
using namespace std;

struct DoublyLinkedList {
    struct Node {
        // const int innerRadius = 26;
        // const int outerRadius = 30;
        // const int characterSize = 20;
        // const int lineThickness = 4;
        // const int arrowWidth = 6;
        // const int arrowHeight = 8;
        // Data
        int data;
        Node *pNext, *pPrev;

        // Position
        Vector2 centerFrom, center; // Centers of the circle

        // Line
        Vector2 arrowHeadStart1, arrowHeadStart2, arrowHeadStart3; // Coordinates of the arrow head 1
        Vector2 arrowHeadEnd1, arrowHeadEnd2, arrowHeadEnd3; // Coordinates of the arrow head 2

        // Direction
        int direction;

        // Content
        char label[5];
        int labelLength;

        // Initialize
        Node(void);
        Node(int data, Node *pPrev, Node* pNext);
        void makeLabel(void); // initialize the label of the node
        void makePosition(bool isNew); // initialize the position of the node or shift after insertion

        // Update
        void update(void); // update node's attributes
        void updatePosition(void); // update node's position
        void updateLine(void); // update line connecting with the previous node (if exists): arrowHeadStart1, arrowHeadStart2, arrowHeadStart3, arrowHeadEnd1, arrowHeadEnd2, arrowHead3

        // Draw
        void drawLine(void); // draw line (if exists)
        void drawNode(void); // draw node and content

        // Set
        void setPosition(Vector2 pos);
    };
    
    int n;
    Node *head, *tail;

    DoublyLinkedList(void);
    ~DoublyLinkedList(void);
    void draw(void); // draw the entire list
    void update(void);
    void random(int n); // randomize with number of nodes
    void removeAll(void); // remove all nodes
    void insertHead(int x); // insert a new node at the head
    void insertTail(int x); // insert a new node at the tail
    void insertAfter(int p, int x); // insert a new node after node with index p (0-indexed)
    void build(vector<int>& vi); // build a linked list with given vector<int>
};