#include "../header/PTaskManagement.h"

PTaskManagement::PTaskManagement(void) : step(0) {}

void PTaskManagement::takeRequest(vector<string> request) {
    if(request[0] == "nothing")
        return;
    
    taskQueue.push(request);
}

int PTaskManagement::getStep(void) {
    return step;
}

void PTaskManagement::nextStep(void) {
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

    step = 0;
    taskQueue.pop();
}