#pragma once
#include <raylib.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode{
    int val;
    int height;

    Vector2 position;
    float radius;
    TreeNode *left, *right;
    TreeNode(int x);
};

struct AVL {
    TreeNode* TreeRoot;
    vector<TreeNode*> allNode;
    AVL();
    int getBalance(TreeNode* root);
    void setHeight(TreeNode* &root);
    void update_x(TreeNode* &root, bool direction);
    void update_y(TreeNode* &root, bool direction);
    void FixPosition(TreeNode* &root, int x);
    int findUpdateIndex(vector<bool> v, bool find);
    TreeNode* insertNode(int x);
    TreeNode* rotateLeft(TreeNode* &root);
    TreeNode* rotateRight(TreeNode* &root);
    void draw();
};