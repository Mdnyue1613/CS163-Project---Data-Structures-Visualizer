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

TreeNode* AVL::rotateLeft(TreeNode* &root) {
    TreeNode* newRoot = root->right;
    TreeNode* newChild = newRoot->left;

    newRoot->parent = root->parent;
    root->parent = newRoot;
    if(newChild) newChild->parent = root;

    newRoot->left = root;
    root->right = newChild;

    if(newChild) newChild->isLeft = false;
    root->isLeft = true;

    setHeight(root);
    setHeight(newRoot);
    return newRoot;
}

TreeNode * AVL::rotateRight(TreeNode* &root) {
    TreeNode* newRoot = root->left;
    TreeNode* newChild = newRoot->right;

    newRoot->parent = root->parent;
    root->parent = newRoot;
    if(newChild) newChild->parent = root;

    newRoot->right = root;
    root->left = newChild;

    if(newChild) newChild->isLeft = true;
    root->isLeft = false;

    setHeight(root);
    setHeight(newRoot);
    return newRoot;
}

TreeNode* AVL::insertNode(int x) {
    vector<TreeNode*> path;
    vector<bool> direction;
    if (!TreeRoot) {
        TreeRoot = new TreeNode(x);
        TreeRoot->parent = nullptr;
        TreeRoot->isLeft = false;
        TreeRoot->position = {600, 400};
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
            Parent->left = new TreeNode(x);
            toInsert = Parent->left;
            toInsert->parent = Parent;
            toInsert->position = {Parent->position.x - distance_x, Parent->position.y + distance_y};
            toInsert->isLeft = true;
        }
        else if (x > Parent->val) {
            Parent->right = new TreeNode(x);
            toInsert = Parent->right;
            toInsert->parent = Parent;
            toInsert->position = {Parent->position.x + distance_x, Parent->position.y + distance_y};
            toInsert->isLeft = false;
        }
        while (!path.empty()) {
            TreeNode* cur = path.back();
            path.pop_back();
            setHeight(cur);
            bool curDirection;
            if(!direction.empty()) curDirection = direction.back();
            direction.pop_back();
            if(getBalance(cur) > 1) { //imbalance to the left
                if(cur->left && getBalance(cur->left) < 0) { // left right problem
                    TreeNode* tmp = rotateLeft(cur->left);
                    cur->left = tmp;
                    tmp->parent = cur;
                }
                if (path.empty()) {
                    TreeRoot = rotateRight(cur);
                }
                else if (curDirection == 1) {
                    path.back()->right = rotateRight(cur);
                }
                else if (curDirection == 0) path.back()->left = rotateRight(cur);
            }
            else if (getBalance(cur) < -1) { // imbalance to the right
                if(cur->right && getBalance(cur->right) > 0) { // right left problem
                    TreeNode* tmp = rotateRight(cur->right);
                    cur->right = tmp;
                    tmp->parent = cur;
                }
                if (path.empty()) {
                    TreeRoot = rotateLeft(cur);
                }
                else if (curDirection == 1) {
                    path.back()->right = rotateLeft(cur);
                }
                else if (curDirection == 0) path.back()->left = rotateLeft(cur);
            }
        }
    }
    updateTreePosition();
    return TreeRoot;
}

void AVL::draw() {
        for (auto Node : allNode) {
            if (Node->left) {
                Vector2 pointNode;
                Vector2 pointLeft;
                float dis = (Node->position.x - Node->left->position.x) *  (Node->position.x - Node->left->position.x) + (Node->position.y - Node->left->position.y) * (Node->position.y - Node->left->position.y);
                dis = sqrt(dis);
                float dis_x = (Node->position.x - Node->left->position.x);
                float dis_y = (Node->left->position.y - Node->position.y);
                float delta_x = (dis_x / dis) * Node->radius;
                float delta_y = (dis_y / dis) * Node->radius;
                pointNode = {Node->position.x - delta_x, Node->position.y + delta_y};
                pointLeft = {Node->left->position.x + delta_x, Node->left->position.y - delta_y};
                DrawLineEx(pointNode, pointLeft, 2.0, BLACK);
            }
            if (Node->right) {
                Vector2 pointNode;
                Vector2 pointRight;
                float dis = (Node->position.x - Node->right->position.x) *  (Node->position.x - Node->right->position.x) + (Node->position.y - Node->right->position.y) * (Node->position.y - Node->right->position.y);
                dis = sqrt(dis);
                float dis_x = (Node->right->position.x - Node->position.x);
                float dis_y = (Node->right->position.y - Node->position.y);
                float delta_x = (dis_x / dis) * Node->radius;
                float delta_y = (dis_y / dis) * Node->radius;
                pointNode = {Node->position.x + delta_x, Node->position.y + delta_y};
                pointRight = {Node->right->position.x - delta_x, Node->right->position.y - delta_y};
                DrawLineEx(pointNode, pointRight, 2.0, BLACK);
            }
            DrawCircle(Node->position.x, Node->position.y, Node->radius, BLUE);
            string s = to_string(Node->val);
            DrawText(s.c_str(), Node->position.x, Node->position.y, Node->radius,WHITE);
        }
}

void AVL::removeAll() {
    for (auto& Node : allNode) {
        delete Node;
        Node = nullptr;
    }
    TreeRoot = nullptr;
    allNode.clear();
}

AVL::~AVL() {
    removeAll();
}

void AVL::random(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 30);
    
    if(TreeRoot){
        removeAll();
    }
    for(int i = 0; i < n; i++) {
        TreeRoot = insertNode(dist(gen));
    }
}

void AVL::moveTree(TreeNode *&root, bool direction) {
    if (!root) return;
    root->position.x += (direction ? distance_x : -distance_x);
    moveTree(root->left, 0);
    moveTree(root->right, 1);
}

void AVL::updateTreePosition() {
    if (!TreeRoot) return;
    allNode.clear();
    queue<TreeNode*> q;
    q.push(TreeRoot);
    while (!q.empty()) {
        TreeNode* tmp = q.front();
        q.pop();
        allNode.push_back(tmp);
        if(tmp->left) q.push(tmp->left);
        if(tmp->right) q.push(tmp->right);
    }

    for (auto& Node : allNode) {
        if (Node == TreeRoot) {
            Node->position = {600, 400};
        }
        else {
            TreeNode* cur = TreeRoot;
            while(cur) {
                if (Node->val < cur->val) {
                    if (cur->left && cur->left->val < Node->val) moveTree(cur->left, 0);
                    cur = cur->left;
                }
                else if (Node->val > cur->val) {
                    if (cur->right && cur->right->val > Node->val) moveTree(cur->right, 1);
                    cur = cur->right;
                }
                else {
                    Node->position = {Node->parent->position.x + (Node->isLeft ? -distance_x : distance_x), Node->parent->position.y + distance_y};
                    break;
                }
            }
        }
    }
}