#pragma once
#include <iostream>
#include "DoublyLinkedList.h"
#include "PTaskManagement.h"
using namespace std;

struct PDSAnimation {
    DoublyLinkedList * dataStructurePointer;
    PTaskManagement * taskManagementPointer;
    bool waitRequest;

    PDSAnimation(void);
    PDSAnimation(DoublyLinkedList * dataStructurePointer, PTaskManagement * taskManagementPointer);

    // Step by step request
    enum SBSRequest {
        noRequest,
        skipBackward,
        goBackward,
        play,
        goForward,
        skipForward
    };

    // Insert animations
    bool insertHead(int value, int stepRequest, string& explanationText); // Insert an element at the head of the list, Return true if the progress is done
    // Step in forward direction: return true if the insert progress is done
    bool insertHeadStep0(int value, int stepRequest, string& explanationText); // Step 0
    bool insertHeadStep1(int value, int stepRequest, string& explanationText); // Step 1
    bool insertHeadStep2(int value, int stepRequest, string& explanationText); // Step 2
    bool insertHeadStep3(int value, int stepRequest, string& explanationText); // Step 3
    bool insertHeadStep4(int value, int stepRequest, string& explanationText); // Step 4
    // Undo step
    bool undoInsertHead0(int value, int stepRequest, string& explanationText); // Move from step 1 -> 0
    bool undoInsertHead1(int value, int stepRequest, string& explanationText); // Move from step 2 -> 1
    bool undoInsertHead2(int value, int stepRequest, string& explanationText); // Move from step 3 -> 2
    bool undoInsertHead3(int value, int stepRequest, string& explanationText); // Move from step 4 -> 3

    bool insertTail(int value, int stepRequest, string& explanationText); // Insert an element at the end of the list, Return ture if the progress is done
    bool insertAfter(int position, int value, int stepRequest, string& explanationText); // Insert an element after a specified position in the list, Return true if the progress is done
};