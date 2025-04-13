#include "../header/PTaskManagement.h"

PTaskManagement::PTaskManagement(void) : step(0), time(0.f) {}

void PTaskManagement::takeRequest(vector<string> request) {
    if(request[0] == "nothing")
        return;
    
    taskQueue.push(request);
}

void PTaskManagement::takeCondition(bool condition) {
    conditionStack.push(condition);
}

bool PTaskManagement::getCondition(void) {
    if(conditionStack.empty()) {
        cerr << "Error: PTaskManagement::getCondition()\n";
        exit(1);
    }
    return conditionStack.top();
}

void PTaskManagement::popCondition(void) {
    conditionStack.pop();
}

int PTaskManagement::getNumCondition(void) {
    return conditionStack.size();
}

int PTaskManagement::getStep(void) {
    return step;
}

void PTaskManagement::nextStep(void) {
    time = 0;
    step++;
}

int PTaskManagement::getTaskType(void) {
    // Manage error
    if(taskQueue.empty())
        return NoRequest;

    string type = taskQueue.front()[0];
    if(type == "initialize")
        return Initilize;
    else if(type == "insert")
        return Insert;
    else if(type == "delete") 
        return Delete;
    else if(type == "search")
        return Search;
    
    return NoRequest;
}

vector<string> PTaskManagement::getTask(void) {
    if(taskQueue.empty())
        return {"NoRequest"};

    return taskQueue.front();
}

void PTaskManagement::nextTask(void) {
    // Manage errors
    if(taskQueue.empty()) {
        cerr << "taskQueue in PTaskManagement is empty.\n";
        exit(0);
    }

    time = 0.f;

    step = 0;
    
    taskQueue.pop();
}

void PTaskManagement::updateTime(void) {
    time += GetFrameTime();
}

float PTaskManagement::getTime(void) {
    return time;
}

void PTaskManagement::redoLoop(void) {
    time = 0.f;
}