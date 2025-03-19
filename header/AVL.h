#pragma once
#include <raylib.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <random>
#include <chrono>
#include <thread>
using namespace std;

struct TreeNode{
    int val;
    int height;
    bool isLeft;
    Vector2 position;
    float radius;
    TreeNode *left, *right, *parent;
    TreeNode(int x);
};

struct AVL {
    TreeNode* TreeRoot;
    vector<TreeNode*> allNode;
    const float distance_x = 60;
    const float distance_y = 60;
    AVL();
    int getBalance(TreeNode* root);
    void setHeight(TreeNode* &root);
    void update_x(TreeNode* &root, bool direction);
    TreeNode* insertNode(int x);
    TreeNode* rotateLeft(TreeNode* &root);
    TreeNode* rotateRight(TreeNode* &root);
    void removeAll();
    ~AVL();
    void random(int n);
    void draw();
    void moveTree(TreeNode *&root, bool distance);
    void updateTreePosition();
};