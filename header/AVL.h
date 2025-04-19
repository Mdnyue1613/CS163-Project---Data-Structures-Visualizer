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
#include"PExplanationArea.h"
#include"LPseudoCode.h"
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
    TreeNode(TreeNode& other) {
        val = other.val;
        height = other.height;
        isLeft = other.isLeft;
        isHighlight = other.isHighlight;
        position = other.position;
        targetPosition = other.targetPosition;
        radius = other.radius;
        color = other.color;
        left = right = parent = nullptr;
    }
    TreeNode(int x, Color color);
    void setRadius(float radius);
    void setColor(Color color);
};
/*
    TreeRootStack.push(new TreeNode(*avl.TreeRoot));
*/
struct AVL {
    TreeNode* TreeRoot;
    TreeNode* rotationNode = nullptr;
    TreeNode* NodeInsert = nullptr;
    TreeNode* childRotateNode = nullptr;
    TreeNode* NodeDelete = nullptr;
    TreeNode* newDeleteNode = nullptr;
    TreeNode* selectionNode = nullptr;
    int indexOfDeleteNodeInPath = 0;
    int findData;
    bool isInsert, isDelete, isFind, isInit;
    bool isNeedToFindAnotherDeleteNode = false;
    bool isNeedToRotate = false, isNeedToRotateChild = false;
    vector<TreeNode*> allNode, Path;
    Vector2 rootPosition = {750, 200};
    float distance_x;
    float distance_y;
    float animationSpeed = 1.f;
    int animationStep = 0;
    int hightLightNodeIndex = 0;
    Color treeColor = BLUE;
    Color highlightColor = YELLOW;
    Color warningColor = RED;
    Color selectionNodeColor = DARKBLUE;
    Color choosenNodeColor = GREEN;

    PExplanationArea explanationArea;
    LPseudoCode PseudoCodeArea;
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
    void vectorIntInit(vector<int> nums);
    void draw();
    void moveTree(TreeNode *&root, bool distance);
    void updateTreePosition();
    void setTreeSize(TreeNode*& root, float raidus);
    void initializeAnimation();
    void insertAnimation();
    void deleteAnimation();
    void findAnimation();
    void drawTree();
    void setCurrentPosition(float speed);
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
    void findNode(TreeNode*& root, int x);
    void setAnimationSpeed(float speed);
    void setTreeColor(Color color);
    void setHighlightColor(Color color);
    void setWarningColor(Color color);
    void setSelectionNodeColor(Color color);
    void setChoosenNodeColor(Color color);
};