#include <stack>
#include "raylib.h"

using namespace std;

struct TreeNode {
    int val, height;
    TreeNode *left, *right;
    TreeNode(int x);
};

struct AVL {
    TreeNode *Node;
    AVL *left, *right;
    pair<float, float> oldPos, newPos;
    AVL();
    TreeNode* rotateLeft(TreeNode *&root);
    TreeNode* rotateRight(TreeNode *&root);
    TreeNode* insertNode(TreeNode *&root, int x);
    int getBalance(TreeNode* root);
    int getHeight(TreeNode* root);
};