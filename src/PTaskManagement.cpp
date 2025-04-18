#include "../header/PTaskManagement.h"

PTaskManagement::PTaskManagement(void) : step(0), time(0.f), taskDone(false) {
    task.clear();
}

bool PTaskManagement::takeRequest(vector<string> request) {
    if(doneTask() == false)
        return false;

    if(request.size() == 1 || request[1] == "nothing") {
        return false;
    }
    
    nextTask();
    task = request;
    return true;
}

void PTaskManagement::pushRecursionStack(TreeNode** node) {
    TreeNodeRecursionStack.push_back(node);
}

void PTaskManagement::popRecursionStack(void) {
    if((int)TreeNodeRecursionStack.empty()) {
        cerr << "Error: PTaskManagement::popRecursionStack()\n";
        exit(1);
    }
    TreeNodeRecursionStack.pop_back();
}

int PTaskManagement::getRecursionStackSize(void) {
    return TreeNodeRecursionStack.size();
}

TreeNode** PTaskManagement::getTreeNode(int i) {
    if(i >= (int)TreeNodeRecursionStack.size()) {
        cerr << "Error: PTaskManagement::getTreeNode()\n";
        exit(1);
    }
    return TreeNodeRecursionStack[TreeNodeRecursionStack.size() - 1 - i];
}

void PTaskManagement::takeCondition(bool condition) {
    conditionStack.push_back(condition);
}

bool PTaskManagement::getCondition(int i) {
    if(i >= (int)conditionStack.size()) {
        cerr << "Error: PTaskManagement::getCondition(" << i << ")\n";
        exit(1);
    }
    return conditionStack[i];
}

void PTaskManagement::popCondition(void) {
    conditionStack.pop_back();
}

int PTaskManagement::getNumCondition(void) {
    return conditionStack.size();
}

int PTaskManagement::getStep(void) {
    return step;
}

void PTaskManagement::nextStep(void) {
    time = 0.f;
    step++;
}

void PTaskManagement::prevStep(void) {
    time = 0.f;
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
    else if(type == "remove") 
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