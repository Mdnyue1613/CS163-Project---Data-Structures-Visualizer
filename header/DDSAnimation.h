#pragma once
#include "Hashtable.h"
#include "PTaskManagement.h"
#include <iostream>
using namespace std;

struct DDSAnimation
{
    Hashtable * dataStructurePointer;
    PTaskManagement * taskManagementPointer;
    bool waitRequest;
    stack<string> undoStack;
    stack<pair<bool *, bool>> undoBoolStack;
    stack<pair<int *, int>> undoIntStack;
    stack<pair<float *, float>> undoFloatStack;
    stack<pair<vector<bool> *, vector<bool>>> undoVectorBoolStack;
    stack<pair<vector<AnimatedSquare> *, vector<AnimatedSquare>>> undoVectorAnimatedSquareStack;

    enum requestTypeID
    {
        noRequest,
        skipBackward,
        goBackward,
        play,
        goForward,
        skipForward
    };

    void reset(void);

    // Record version
    void makeVersion(void);
    void recordBool(bool * p);
    void recordInt(int * p);
    void recordFloat(float * p);
    void recordVectorBool(vector<bool> * p);
    void recordVectorAnimatedSquare(vector<AnimatedSquare> * p);

    // Undo
    bool undo(int stepRequest); // Undo the last step, always return false because the animation is not done yet
    void undoBool(void);
    void undoInt(void);
    void undoFloat(void);
    void undoVectorBool(void);
    void undoVectorAnimatedSquare(void);

    // Insert animation
    bool insert(int value, int stepRequest, string& explanationText, int& codeLine); // Insert an element into the hash table, Return true if the progress is done
    bool insertStep0(int value, int stepRequest, string& explanationText, int& codeLine); // Step 0
    bool insertStep1(int value, int stepRequest, string& explanationText, int& codeLine); // Step 1
    bool insertStep2(int value, int stepRequest, string& explanationText, int& codeLine); // Step 2
    bool insertStep3(int value, int stepRequest, string& explanationText, int& codeLine); // Step 3
    bool insertStep4(int value, int stepRequest, string& explanationText, int& codeLine); // Step 4
    bool insertStep5(int value, int stepRequest, string& explanationText, int& codeLine); // Step 5

    // Remove animation
    bool remove(int value, int stepRequest, string& explanationText, int& codeLine);
    bool removeStep0(int value, int stepRequest, string& explanationText, int& codeLine); // Step 0
    bool removeStep1(int value, int stepRequest, string& explanationText, int& codeLine); // Step 1
    bool removeStep2(int value, int stepRequest, string& explanationText, int& codeLine); // Step 2   
    bool removeStep3(int value, int stepRequest, string& explanationText, int& codeLine); // Step 3
    bool removeStep4(int value, int stepRequest, string& explanationText, int& codeLine); // Step 4

    // Search animation
    bool search(int value, int stepRequest, string& explanationText, int& codeLine); // Search an element in the hash table, Return true if the progress is done
    bool searchStep0(int value, int stepRequest, string& explanationText, int& codeLine); // Step 0
    bool searchStep1(int value, int stepRequest, string& explanationText, int& codeLine); // Step 1
    bool searchStep2(int value, int stepRequest, string& explanationText, int& codeLine); // Step 2
    bool searchStep3(int value, int stepRequest, string& explanationText, int& codeLine); // Step 3
    bool searchStep4(int value, int stepRequest, string& explanationText, int& codeLine); // Step 4



};
