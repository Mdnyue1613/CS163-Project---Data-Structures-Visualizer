#pragma once
#include <iostream>
#include "DoublyLinkedList.h"
#include "PTaskManagement.h"
using namespace std;

struct PDSAnimation {
    DoublyLinkedList * dataStructurePointer;
    PTaskManagement * taskManagementPointer;

    PDSAnimation(void);
    PDSAnimation(DoublyLinkedList * dataStructurePointer, PTaskManagement * taskManagementPointer);

    // Insert animations
    bool insertHead(int value); // Insert an element at the head of the list, Return true if the progress is done
    bool insertTail(int value); // Insert an element at the end of the list, Return ture if the progress is done
    bool insertAfter(int position, int value); // Insert an element after a specified position in the list, Return true if the progress is done
};