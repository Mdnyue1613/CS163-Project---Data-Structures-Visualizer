#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<string>
#include<raylib.h>
#include"LTreeNode.h"
using namespace std;

struct PTaskManagement {
    /*
        Data structure to manage tasks:
            - In one task has many steps
            - nextStep(): update after completing a step
            - nextTask(): update after completing a task
    */
    int step;
    vector<string> task;
    bool taskDone;
    vector<bool> conditionStack, undoCondtionStack;
    float time;
    vector<TreeNode**> TreeNodeRecursionStack;

    PTaskManagement(void);

    // Recursion
    void pushRecursionStack(TreeNode** node); // Push new node into the recursion stack
    void popRecursionStack(void); // Pop the lastest node in the recursion stack
    int getRecursionStackSize(void); // Get the size of the recursion stack
    TreeNode** getTreeNode(int i = 0); // Get the lastest node in the recursion stack

    // Condition stack
    void takeCondition(bool condition); // Push new condition into the condition stack
    bool getCondition(int i = 0); // Get the lastest condition
    void popCondition(void); // Delete the lastest condition
    int getNumCondition(void); // Get the number of conditions

    // Step
    int getStep(void); // Return 'step'
    void nextStep(void); // Go to the next step
    void prevStep(void); // Go to the previous step

    // Task
    enum taskType {
        Initilize,
        Insert,
        Delete, 
        Search,
        NoRequest
    };
    bool takeRequest(vector<string> request); // Push new request into task queue, return true if pushed a new request
    int getTaskType(void); // Get the type of the task
    vector<string> getTask(void); // Get the task
    void endTask(void); // End a task
    void nextTask(void); // Go to the next task
    bool doneTask(void); // Return if the task is done

    // Time
    void updateTime(void);
    float getTime(void);

    // Loop
    void redoLoop(void);
};