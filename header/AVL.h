#pragma once
#include <raylib.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <random>
#include <chrono>
#include <thread>
#include <set>
#include <iostream>
using namespace std;

struct TreeNode{
    int val;
    int height;
    bool isLeft;
    bool isHighlight = 0;
    Vector2 position;
    Vector2 targetPosition;
    float radius;
    Color color;

    TreeNode *left, *right, *parent;
    TreeNode(int x);
    void setRadius(float radius);
    void setColor(Color color);
};

struct AVL {
    TreeNode* TreeRoot;
    TreeNode* rotationNode = nullptr;
    TreeNode* NodeInsert = nullptr;
    TreeNode* childRotateNode = nullptr;
    TreeNode* NodeDelete = nullptr;
    TreeNode* newDeleteNode = nullptr;
    int indexOfDeleteNodeInPath = 0;
    bool isInsert, isDelete, isFind, isInit;
    bool isNeedToRotate = false, isNeedToRotateChild = false;
    vector<TreeNode*> allNode, Path;
    float distance_x;
    float distance_y;
    float animationProgress = 0.f;
    int animationStep = 0;
    int hightLightNodeIndex = 0;
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
    void insertAnimation();
    void deleteAnimation();
    void findAnimation();
    void drawTree();
    void setCurrentPosition();
    void checkRotation();
    void rotateNode(TreeNode*& root);
    void animateRotation();
    void appearNode();
    void disapearnode();
    void defaultTree();
    void hightLightNode();
    void rotateChildNode();
    void checkRotateChildNode();
    void rotateImbalanceNode();
    void setPositionImmediately();
    void insertNodeWithNoAnimation(TreeNode *&root, TreeNode *parent, int x);
    void deleteNodeRunAtOnce(TreeNode*& root, TreeNode* parent, int x);
    void deleteWithNoAnimation(TreeNode*& root, TreeNode* parent, int x);
    void FindDeleteNode(TreeNode*& root, TreeNode* parent, int x);
    void FindNewDeleteNode(TreeNode*& root);
    void prePareTreeForDelete();
    void updatePathAfterDelete();
    void updateHeightInPath();
    void insertNodeRunAtOnce(TreeNode *&root, TreeNode *parent, int x);
};