#include "../header/AVL.h"

int TreeNode::getBalance() {
    int lheight = left ? left->height : 0;
    int rheight = right ? right->height : 0;
    int balance = lheight - rheight;
    return balance;
}

void TreeNode::setHeight() {
    int lheight = left ? left->height : 0;
    int rheight = right ? right->height : 0;
    this->height = 1 + max(lheight, rheight);
}

TreeNode::TreeNode(int x) {
    val = x;
    left = right = nullptr;
    height = 1;
    radius = 20;
}

void TreeNode::update_x(TreeNode* root, bool direction) {
    if (root == nullptr) return;
    if (direction == 1) {
        root->position.x += 2 * radius;
    }
    else {
        root->position.x -= 2 * radius;
    }
    update_x(root->left, direction);
    update_x(root->right, direction);
}

void TreeNode::update_y(TreeNode* root, bool direction) {
    if (root == nullptr) return;
    if (direction == 1) {
        root->position.y += 2 * radius;
    }
    else {
        root->position.y -= 2 * radius;
    }
    update_y(root->left, direction);
    update_y(root->right, direction);
}

int TreeNode::findUpdateIndex(vector<bool> v, bool find) {
    int n = v.size() - 1;
    int res = -1;
    for (int i = n; i >= 0; i--) {
        if (v[i] == find) return i;
    }
    return res;
}

TreeNode* TreeNode::rotateLeft(TreeNode* &root) {
    TreeNode* tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    root->setHeight();
    tmp->setHeight();
    update_y(tmp->right, 1);
    update_y(root->left, 0);
    root->position.y -= 2 * radius;
    tmp->position.y += 2 * radius;
    return tmp;
}

TreeNode * TreeNode::rotateRight(TreeNode* &root) {
    TreeNode* tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    root->setHeight();
    tmp->setHeight();
    update_y(tmp->left, 1);
    update_y(root->right, 0);
    root->position.y -= 2 * radius;
    tmp->position.y += 2 * radius;
    return tmp;
}

TreeNode* TreeNode::insertNode(TreeNode* &root, int x) {
    vector<TreeNode*> path;
    vector<bool> direction;
    if (!root) {
        root = new TreeNode(x);
        root->position = {600, 400};
    }
    else {
        path.push_back(root);
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
            toInsert->position = {Parent->position.x - radius, Parent->position.y + 2 * radius};
        }
        else if (x > Parent->val) {
            int updateIndex = findUpdateIndex(direction, 0) + 1;
            update_x(path[updateIndex], direction[0]);
            Parent->right = new TreeNode(x);
            toInsert = Parent->right;
            toInsert->position = {Parent->position.x + radius, Parent->position.y + 2 * radius};
        }
        else return root;
        while (!path.empty()) {
            TreeNode* cur = path.back();
            path.pop_back();
            cur->setHeight();
            int curDirection;
            if (direction.empty()) curDirection = -1;
            else {
                curDirection = (int) direction.back();
                direction.pop_back();
            }
            if(cur->getBalance() < -1) {
                if(cur->left->getBalance() < 0) cur->left = rotateRight(cur->left);
                if (curDirection == 1) {
                    path.back()->right = rotateLeft(cur);
                }
                else if (curDirection == 0) path.back()->left = rotateLeft(cur);
                else if (curDirection == -1) cur = cur->rotateLeft(cur);
            }
            else if (cur->getBalance() > 1) {
                if(cur->right->getBalance() > 0) cur->right = rotateLeft(cur->right);
                if (curDirection == 1) {
                    path.back()->right = rotateRight(cur);
                }
                else if (curDirection == 0) path.back()->left = rotateRight(cur);
                else if (curDirection == -1) cur = cur->rotateRight(cur);
            }
        }
    }
    return root;
}