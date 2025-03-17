#include "../header/AVL.h"
#include <string>
#include <cstring>

TreeNode::TreeNode(int x) {
    val = x;
    left = right = nullptr;
    height = 1;
    radius = 20;
}

AVL::AVL() {
    TreeRoot = nullptr;
    allNode.resize(0);
}

int AVL::getBalance(TreeNode* root) {
    int lheight = root->left ? root->left->height : 0;
    int rheight = root->right ? root->right->height : 0;
    int balance = lheight - rheight;
    return balance;
}

void AVL::setHeight(TreeNode* &root) {
    int lheight = root->left ? root->left->height : 0;
    int rheight = root->right ? root->right->height : 0;
    root->height = 1 + max(lheight, rheight);
}

void AVL::update_x(TreeNode* &root, bool direction) {
    if (root == nullptr) return;
    if (direction == 1) {
        root->position.x += 2 * root->radius;
    }
    else {
        root->position.x -= 2 * root->radius;
    }
    update_x(root->left, direction);
    update_x(root->right, direction);
}

void AVL::update_y(TreeNode* &root, bool direction) {
    if (root == nullptr) return;
    if (direction == 1) {
        root->position.y += 2 * root->radius;
    }
    else {
        root->position.y -= 2 * root->radius;
    }
    update_y(root->left, direction);
    update_y(root->right, direction);
}

void AVL::FixPosition(TreeNode* &root, int x) {
    if (!root) return;
    if(root->position.x == x) return;
    float ld = root->left ? root->position.x - root->left->position.x : 0;
    float rd = root->right ? root->right->position.x - root->position.x : 0;
    root->position.x = x;
    FixPosition(root->left, x - ld);
    FixPosition(root->right, x + rd);
}

int AVL::findUpdateIndex(vector<bool> v, bool find) {
    int n = v.size() - 1;
    int res = -1;
    for (int i = n; i >= 0; i--) {
        if (v[i] == find) return i;
    }
    return res;
}

TreeNode* AVL::rotateLeft(TreeNode* &root) {
    if (!root || !root->right) return root;
    TreeNode* tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    setHeight(root);
    setHeight(tmp);
    update_y(tmp->right, 0);
    update_y(root->left, 1);
    root->position.y += 2 * root->radius;
    tmp->position.y -= 2 * tmp->radius;
    return tmp;
}

TreeNode * AVL::rotateRight(TreeNode* &root) {
    if (!root || !root->left) return root;
    TreeNode* tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    setHeight(root);
    setHeight(tmp);
    update_y(tmp->left, 0);
    update_y(root->right, 1);
    root->position.y += 2 * root->radius;
    tmp->position.y -= 2 * tmp->radius;
    return tmp;
}

TreeNode* AVL::insertNode(int x) {
    vector<TreeNode*> path;
    vector<bool> direction;
    if (!TreeRoot) {
        TreeRoot = new TreeNode(x);
        TreeRoot->position = {600, 400};
        allNode.push_back(TreeRoot);
    }
    else {
        path.push_back(TreeRoot);
        while(true) {
            TreeNode* tmp = path.back();
            TreeNode* nextNode = nullptr;
            if (x < tmp->val) {
                nextNode = tmp->left;
                direction.push_back(0);
            }
            else if (x > tmp->val) {
                nextNode = tmp->right;
                direction.push_back(1);
            }
            if (nextNode == nullptr) break;
                path.push_back(nextNode);
        }
        TreeNode* Parent = path.back();
        TreeNode* toInsert = nullptr;
        if (x < Parent->val) {
            int updateIndex = findUpdateIndex(direction, 1) + 1;
            update_x(path[updateIndex], direction[0]);
            Parent->left = new TreeNode(x);
            toInsert = Parent->left;
            toInsert->position = {Parent->position.x - Parent->radius, Parent->position.y + 2 * Parent->radius};
            allNode.push_back(toInsert);
        }
        else if (x > Parent->val) {
            int updateIndex = findUpdateIndex(direction, 0) + 1;
            update_x(path[updateIndex], direction[0]);
            Parent->right = new TreeNode(x);
            toInsert = Parent->right;
            toInsert->position = {Parent->position.x + Parent->radius, Parent->position.y + 2 * Parent->radius};
            allNode.push_back(toInsert);
        }
        else return TreeRoot;
        while (!path.empty()) {
            TreeNode* cur = path.back();
            path.pop_back();
            setHeight(cur);
            int curDirection;
            curDirection = (int) direction.back();
            direction.pop_back();
            if(getBalance(cur) > 1) { //imbalance to the left
                if(cur->left && getBalance(cur->left) < 0) cur->left = rotateLeft(cur->left);
                if (path.empty()) {
                    TreeRoot = rotateRight(cur);
                }
                else if (curDirection == 1) {
                    path.back()->right = rotateRight(cur);
                }
                else if (curDirection == 0) path.back()->left = rotateRight(cur);
            }
            else if (getBalance(cur) < -1) { // imbalance to the right
                if(cur->right && getBalance(cur->right) > 0) cur->right = rotateRight(cur->right);
                if (path.empty()) {
                    TreeRoot = rotateLeft(cur);
                }
                else if (curDirection == 1) {
                    path.back()->right = rotateLeft(cur);
                }
                else if (curDirection == 0) path.back()->left = rotateLeft(cur);
            }
            FixPosition(TreeRoot, 600);
        }
    }
    return TreeRoot;
}

void AVL::draw() {
        // DrawCircle(TreeRoot->position.x, TreeRoot->position.y, TreeRoot->radius, BLUE);
        // string s = to_string(TreeRoot->val);
        // DrawText(s.c_str(), TreeRoot->position.x, TreeRoot->position.y, TreeRoot->radius,WHITE);
        for (auto Node : allNode) {
            DrawCircle(Node->position.x, Node->position.y, Node->radius, BLUE);
            string s = to_string(Node->val);
            DrawText(s.c_str(), Node->position.x, Node->position.y, Node->radius,WHITE);
        }
}