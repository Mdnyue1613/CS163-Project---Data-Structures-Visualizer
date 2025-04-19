#pragma once
#include <iostream>
#include "DoublyLinkedList.h"
#include "PTaskManagement.h"
using namespace std;

struct PDSAnimation {
    DoublyLinkedList * dataStructurePointer;
    PTaskManagement * taskManagementPointer;
    bool waitRequest;
    stack<string> undoStack;
    stack<pair<bool *, bool>> undoBoolStack;
    stack<pair<pair<PNode * *, PNode *>, bool>> undoPNodePointerStack;
    stack<pair<PNode **, PNode **>> undoPNodePointerStack2;
    stack<pair<int *, int>> undoIntStack;
    stack<pair<float *, float>> undoFloatStack;
    stack<pair<vector<bool> *, vector<bool>>> undoVectorBoolStack;
    stack<pair<PNode **, PNode>> undoDeletePNodePointerStack;
    stack<pair<Vector2 *, Vector2>> undoVector2Stack;

    PDSAnimation(void);
    PDSAnimation(DoublyLinkedList * dataStructurePointer, PTaskManagement * taskManagementPointer);

    void reset(void);

    // Step by step request
    enum SBSRequest {
        noRequest,
        skipBackward,
        goBackward,
        play,
        goForward,
        skipForward
    };

    // Record version
    void makeVersion(void);
    void recordBool(bool * p);
    void recordPNodePointer(PNode * * p, bool remove);
    void recordPNodePointer2(PNode * * p, PNode * * p2);
    void recordDeletePNodePointer(PNode * * p);
    void recordInt(int * p);
    void recordFloat(float * p);
    void recordVectorBool(vector<bool> * p);
    void recordVector2(Vector2 * p);
    // Undo version
    bool undoVersion(int stepRequest);
    void undoBool(void);
    void undoPNodePointer(void);
    void undoPNodePointer2(void);
    void undoDeletePNodePointer(void);
    void undoInt(void);
    void undoFloat(void);
    void undoVectorBool(void);
    void undoVector2(void);

    // INSERT HEAD
    bool insertHead(int value, int stepRequest, string& explanationText, int& codeLine); // Insert an element at the head of the list, Return true if the progress is done
    // Insert at head steps
    bool insertHeadStep0(int value, int stepRequest, string& explanationText, int& codeLine); // Step 0
    bool insertHeadStep1(int value, int stepRequest, string& explanationText, int& codeLine); // Step 1
    bool insertHeadStep2(int value, int stepRequest, string& explanationText, int& codeLine); // Step 2
    bool insertHeadStep3(int value, int stepRequest, string& explanationText, int& codeLine); // Step 3
    bool insertHeadStep4(int value, int stepRequest, string& explanationText, int& codeLine); // Step 4
    // Undo insert at head steps
    bool undoInsertHead0(int value, int stepRequest, string& explanationText); // Move from step 1 -> 0
    bool undoInsertHead1(int value, int stepRequest, string& explanationText); // Move from step 2 -> 1
    bool undoInsertHead2(int value, int stepRequest, string& explanationText); // Move from step 3 -> 2
    bool undoInsertHead3(int value, int stepRequest, string& explanationText); // Move from step 4 -> 3

    // INSERT TAIL
    bool insertTail(int value, int stepRequest, string& explanationText, int& codeLine); // Insert an element at the end of the list, Return ture if the progress is done
    // Insert at tail steps
    bool insertTailStep0(int value, int stepRequest, string& explanationText, int& codeLine); // Step 0
    bool insertTailStep1(int value, int stepRequest, string& explanationText, int& codeLine); // Step 1
    bool insertTailStep2(int value, int stepRequest, string& explanationText, int& codeLine); // Step 2
    bool insertTailStep3(int value, int stepRequest, string& explanationText, int& codeLine); // Step 3
    bool insertTailStep4(int value, int stepRequest, string& explanationText, int& codeLine); // Step 4

    // INSERT AFTER
    bool insertAfter(int position, int value, int stepRequest, string& explanationText, int& codeLine); // Insert an element after a specified position in the list, Return true if the progress is done
    // Insert after steps
    bool insertAfterStep0(int position, int value, int stepRequest, string& explanationText, int& codeLine); // Step 0
    bool insertAfterStep1(int position, int value, int stepRequest, string& explanationText, int& codeLine); // Step 1
    bool insertAfterStep2(int position, int value, int stepRequest, string& explanationText, int& codeLine); // Step 2
    bool insertAfterStep3(int position, int value, int stepRequest, string& explanationText, int& codeLine); // Step 3
    bool insertAfterStep4(int position, int value, int stepRequest, string& explanationText, int& codeLine); // Step 4
    bool insertAfterStep5(int position, int value, int stepRequest, string& explanationText, int& codeLine); // Step 5
    bool insertAfterStep6(int position, int value, int stepRequest, string& explanationText, int& codeLine); // Step 6
    bool insertAfterStep7(int position, int value, int stepRequest, string& explanationText, int& codeLine); // Step 7
    bool insertAfterStep8(int position, int value, int stepRequest, string& explanationText, int& codeLine); // Step 8
    bool insertAfterStep9(int position, int value, int stepRequest, string& explanationText, int& codeLine); // Step 9
    bool insertAfterStep10(int position, int value, int stepRequest, string& explanationText, int& codeLine); // Step 10
    bool insertAfterStep11(int position, int value, int stepRequest, string& explanationText, int& codeLine); // Step 11
    
    // Remove animations
    bool remove(int position, int stepRequest, string& explanationText, int& codeLine); // Delete an element at a specified position in the list, Return true if the progress is done
    bool removeStep0(int position, int stepRequest, string& explanationText, int& codeLine); // Step 0
    bool removeStep1(int position, int stepRequest, string& explanationText, int& codeLine); // Step 1
    bool removeStep2(int position, int stepRequest, string& explanationText, int& codeLine); // Step 2
    bool removeStep3(int position, int stepRequest, string& explanationText, int& codeLine); // Step 3
    bool removeStep4(int position, int stepRequest, string& explanationText, int& codeLine); // Step 4
    bool removeStep5(int position, int stepRequest, string& explanationText, int& codeLine); // Step 5
    bool removeStep6(int position, int stepRequest, string& explanationText, int& codeLine); // Step 6
    bool removeStep7(int position, int stepRequest, string& explanationText, int& codeLine); // Step 7
    bool removeStep8(int position, int stepRequest, string& explanationText, int& codeLine); // Step 8
    bool removeStep9(int position, int stepRequest, string& explanationText, int& codeLine); // Step 9
    bool removeStep10(int position, int stepRequest, string& explanationText, int& codeLine); // Step 10

    // Search animations
    bool search(int value, int stepRequest, string& explanationText, int& codeLine); // Search an element at a specified position in the list, Return true if the progress is done
    bool searchStep0(int value, int stepRequest, string& explanationText, int& codeLine); // Step 0
    bool searchStep1(int value, int stepRequest, string& explanationText, int& codeLine); // Step 1
    bool searchStep2(int value, int stepRequest, string& explanationText, int& codeLine); // Step 2
    bool searchStep3(int value, int stepRequest, string& explanationText, int& codeLine); // Step 3

    // Update animations
    bool update(PNode* chosen, int value, int stepRequest, string& explanationText, int& codeLine); // Update an element at a specified position in the list, Return true if the progress is done
    bool updateStep0(PNode* chosen, int value, int stepRequest, string& explanationText, int& codeLine); // Step 0
    bool updateStep1(PNode* chosen, int value, int stepRequest, string& explanationText, int& codeLine); // Step 1
    bool updateStep2(PNode* chosen, int value, int stepRequest, string& explanationText, int& codeLine); // Step 2
    bool updateStep3(PNode* chosen, int value, int stepRequest, string& explanationText, int& codeLine); // Step 3
};