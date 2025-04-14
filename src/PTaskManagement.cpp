#include "../header/PTaskManagement.h"

PTaskManagement::PTaskManagement(void) : step(0), time(0.f), taskDone(false) {
    task.clear();
}

void PTaskManagement::takeRequest(vector<string> request) {
    if(doneTask() == false)
        return;

    if(request.size() == 1 || request[1] == "nothing") {
        return;
    }

    cout << "Recieve task ";
    for(string task : request) {
        cout << task << ' ';
    }
    cout << '\n';
    
    nextTask();
    task = request;
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

void PTaskManagement::prevStep(void) {
    time = 0;
    step--;
    taskDone = false;
}

int PTaskManagement::getTaskType(void) {
    if(task.empty())
        return NoRequest;

    string type = task[0];
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
    if(task.empty())
        return {"NoRequest"};

    return task;
}

void PTaskManagement::endTask(void) {
    taskDone = true;
}

void PTaskManagement::nextTask(void) {
    time = 0.f;
    step = 0;
    taskDone = false;
}

bool PTaskManagement::doneTask(void) {
    return task.empty() || taskDone;
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