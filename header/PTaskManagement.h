#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<string>
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

    PTaskManagement(void);

    // Queue
    void takeRequest(vector<string> request); // Push new request into task queue

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
};