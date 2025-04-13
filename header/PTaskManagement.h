#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<string>
#include<raylib.h>
using namespace std;

struct PTaskManagement {
    /*
        Data structure to manage tasks:
            - In one task has many steps
            - nextStep(): update after completing a step
            - nextTask(): update after completing a task
    */
    int step;
    queue<vector<string>> taskQueue;
    stack<bool> conditionStack;
    float time;

    PTaskManagement(void);

    // Task queue
    void takeRequest(vector<string> request); // Push new request into task queue

    // Condition stack
    void takeCondition(bool condition); // Push new condition into the condition stack
    bool getCondition(void); // Get the lastest condition
    void popCondition(void); // Delete the lastest condition
    int getNumCondition(void); // Get the number of conditions

    // Step
    int getStep(void); // Return 'step'
    void nextStep(void); // Go to the next step

    // Task
    enum taskType {
        Initilize,
        Insert,
        Delete, 
        Search,
        NoRequest
    };
    int getTaskType(void); // Get the type of the task
    vector<string> getTask(void); // Get the task
    void nextTask(void); // Go to the next task

    // Time
    void updateTime(void);
    float getTime(void);

    // Loop
    void redoLoop(void);
};