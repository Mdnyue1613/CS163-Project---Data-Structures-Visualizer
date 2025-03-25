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
#include <set>
using namespace std;

struct TreeNode{
    int val;
    int height;
    bool isLeft;
    Vector2 position;
    float radius;
    Color color;

    TreeNode *left, *right, *parent;
    TreeNode(int x);
    void setRadius(TreeNode*& root, float radius);
    void setColor(TreeNode*& root, Color color);
};

struct AVL {
    TreeNode* TreeRoot;
    vector<TreeNode*> allNode;
    float distance_x;
    float distance_y;
    AVL();
    int getBalance(TreeNode *root);
    void setHeight(TreeNode *&root);
    void insertNode(TreeNode *&root, TreeNode *parent, int x);
    void insertNodeNonDuplicate(TreeNode *&root, TreeNode *parent, int x);
    TreeNode* rotateLeft(TreeNode* &root);
    TreeNode* rotateRight(TreeNode* &root);
    void removeAll();
    ~AVL();
    void random(int n);
    void draw();
    void moveTree(TreeNode *&root, bool distance);
    void updateTreePosition();
    void setTreeSize(TreeNode*& root, float raidus);
    void initializeAnimation();
};