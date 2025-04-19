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
    enum nodeType {
        Head,
        Tail,
        Tmp,
        Prev,
        Chosen
    };
    PNode *head, *tail;
    // Animation
    // Tmp
    PNode *animationTmp;
    // Prev
    PNode *animationPrev;
    // Chosen node
    PNode *animationChosen;
    int prevPosition;

    // Constructor
    DoublyLinkedList(void);

    // Destructor
    ~DoublyLinkedList(void);

    // Update
    void update(bool doneTask);
    void updateDataStructure(bool doneTask); // Update the data structure
    void updateAnimation(void);
    void updateInformation(void);
    void quickUpdateAnimation(void); // Skip animation
    void quickUpdateAnimationTmp(void); // Skip animation of animation tmp

    // Draw
    void draw(bool doneTask); // draw all
    void drawDataStructure(bool doneTask); // Draw data structures
    void drawAnimation(void); // draw animations
    void drawAnimationTmp(void);

    // Num node
    int getNumNode(void); // Get the number of nodes
    void addNumNode(int x); // Add x to the number of nodes

    // Instantaneous functions
    void removeAll(void); // remove all nodes
        // Initializing functions
    void randomInitializer(int n); // randomize with number of nodes
    void build(vector<int>& vi); // build a linked list with given vector<int>
        // Inserting functions
    void insertHead(int x); // insert a new node at the head
    void insertTail(int x); // insert a new node at the tail
    void insertAfter(int p, int x); // insert a new node after node with index p (0-indexed)
        // ...
    PNode* getIthNode(int i); // Get the pointer to the i-th node
    void reloadPositions(void); // Reload all positions
    void nextNodePosition(PNode *& node, PNode *& next); // Determine the next node's position, input: node's position, output: next's position

    // Manipulating head
    bool createdHead(void); // Return true if head is created
    void setHighlightHead(bool on); // Set the highlight state of the head node
    void assignAnimationTmpToHead(void); // head = animationTmp
    void assignAnimationTmpToHeadPrev(void); // head->pPrev = animationTmp
    void setHighlightHeadPrevLink(bool on); // set the highlight state of the previous link of the head node
    void setHeadToNull(void); // head = nullptr
    void setHeadPrevLinkToNull(void); // head->pPrev = nullptr

    // Manipulating tail
    void assignAnimationTmpToTail(void); // tail = animationTmp
    void assignAnimationTmpToTailNext(void); // tail->pNext = animationTmp
    void setHighlightTail(bool on);
    void setHighlightTailNextLink(bool on); // set the highlight state of the next link of the tail node
    void setTailToNull(void); // tail = nullptr

    // Manipulating animationTmp
    bool createdAnimationTmp(void); // Return true if createdAnimationTmp
    bool animationTmpIsUpdated(void); // Return true if animationTmp is updated
    void setHighlightAnimationTmp(bool on); // Set the highlight state the the animationTmp node
    void setAnimationTmpToNull(void); // animationTmp = nullptr
    void assignHeadToAnimationTmpNext(void); // animationTmp->pNext = head
    void setHighlightAnimationTmpNextLink(bool on); // Set the highlight state of the next link of animationTmp
    void assignTailToAnimationTmpPrev(void); // animationTmp->pPrev = tail
    void assignAnimationPrevToAnimationTmpPrev(void); // animationTmp->pPrev = animationPrev
    void setHighlightAnimationTmpPrevLink(bool on); // Set the highlight state of the previous link of animationTmp
    void assignAnimationPrevNextToAnimationTmpNext(void); // animationTmp->pNext = animationPrev->pNext
    void assignAnimationTmpToAnimationTmpNextPrev(void); // animationTmp->pNext->pPrev = animationTmp
    void setHighlightAnimationTmpNextPrevLink(bool on); // Set the highlight state of the previous link of animationTmp->pNext
    void deleteAnimationTmp(void); // Delete animationTmp
    void setAnimationTmpNextLinkToNull(void); // animationTmp->pNext = nullptr

    // Manipulating animationPrev
    void assignHeadToAnimationPrev(void); // animationPrev = head
    bool traversePrevDone(int position); // return true if travel prePosition == target position
    void traversePrev(int position); // traverse prev forward
    void setHighlightAnimationPrev(bool on); // set the highlight state of the animation prev
    bool createdAnimationPrev(void); // return animationPrev != nullptr
    void setAnimationPrevToNull(void); // animationPrev = nullptr
    void assignAnimationTmpToAnimationPrevNext(void); // animationPrev->pPnext = animationTmp
    void setHighlightAnimationPrevNextLink(bool on); // set the highlight state of the animationPrev's next link
    void setHighlightAnimationPrevPrevLink(bool on); // set the highlight state of the animationPrev's prev link
    bool isAnimationPrevTail(void); // return animationPrev == tail

    // Animation
    void createANewNode(int x); // Create a new node with value x
    void createNodeBefore(int i, int x); // Create a node with value x and position before the i-th's node
    void createNodeAfter(int i, int x); // Create a node with value x and position after the i-th's node
};