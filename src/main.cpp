#include "../header/GUI.h"
#include "../header/AVL.h"
#include <iostream>
#include <queue>

bool GUI::isOpenMenu = true;
bool GUI::isOpenDS1 = false;
bool GUI::isOpenDS2 = false;
bool GUI::isOpenDS3 = false;
bool GUI::isOpenDS4 = false;

int main() {
    GUI::startProgram();
    TreeNode* root = new TreeNode(0);
    for (int i = 1; i < 10; i++) {
        root = root->insertNode(root, i);
    }
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* tmp = q.front();
        cout << tmp->val << " ";
        q.pop();
        if (tmp->left) q.push(tmp->left);
        if (tmp->right) q.push(tmp->right);
    }
    return 0;
}
