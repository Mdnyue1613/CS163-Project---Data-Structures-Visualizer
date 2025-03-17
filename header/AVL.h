#pragma once
#include <raylib.h>
#include <algorithm>
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
    int getBalance();
    void setHeight();
    void update_x(TreeNode* root, bool direction);
    void update_y(TreeNode* root, bool direction);
    int findUpdateIndex(vector<bool> v, bool find);
    TreeNode* insertNode(TreeNode* &root, int x);
    TreeNode* rotateLeft(TreeNode* &root);
    TreeNode* rotateRight(TreeNode* &root);
};

// struct AVL {
//     TreeNode* root;
//     void draw();
// };