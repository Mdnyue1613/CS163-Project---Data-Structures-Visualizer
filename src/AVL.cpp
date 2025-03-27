#include "../header/AVL.h"
#include <string>
#include <cstring>

TreeNode::TreeNode(int x) {
    val = x;
    left = right = nullptr;
    height = 1;
    radius = 20;
    color = BLUE;
}

void TreeNode::setRadius(float radius) {
    this->radius = radius;
}

void TreeNode::setColor(Color color) {
    this->color = color;
}

AVL::AVL() {
    TreeRoot = nullptr;
    distance_x = 25;
    distance_y = 40;
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
    if (newRoot->parent && newRoot->val < newRoot->parent->val) newRoot->isLeft = true;
    else if (newRoot->parent && newRoot->val > newRoot->parent->val) newRoot->isLeft = false;

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
    if (newRoot->parent && newRoot->val < newRoot->parent->val) newRoot->isLeft = true;
    else if (newRoot->parent && newRoot->val > newRoot->parent->val) newRoot->isLeft = false;
    
    setHeight(root);
    setHeight(newRoot);
    return newRoot;
}

void AVL::insertNode(TreeNode *&root, TreeNode *parent, int x) {
    for(auto Node : allNode) {
        if(x == Node->val) {
            return;
        }
    }
    insertNodeNonDuplicate(root, NULL, x);
    updateTreePosition();
}

void AVL::insertNodeNonDuplicate(TreeNode *&root, TreeNode *parent, int x) {
    if(!root) {
        root = new TreeNode(x);
        allNode.push_back(root);
        root->parent = parent;
        if (parent == nullptr) {
            root->position = {600, 400};
        }
        else {
            if (x < parent->val) {
                root->position.x = parent->position.x - distance_x;
                root->position.y = parent->position.y + distance_y;
                root->isLeft = 1;
            }
            else {
                root->position.x = parent->position.x + distance_x;
                root->position.y = parent->position.y + distance_y;
                root->isLeft = 0;
            }
        }
        return;
    }
    if (x < root->val) insertNodeNonDuplicate(root->left, root, x);
    else if (x > root->val) insertNodeNonDuplicate(root->right, root, x);

    setHeight(root);
    if (getBalance(root) > 1) {
    // imbalance to the left
        if (root->left && getBalance(root->left) < 0) {
            // left-right problem
            root->left = rotateLeft(root->left);
        }
        root = rotateRight(root);
    }
    else if (getBalance(root) < -1) {
        // imbalance to the right
        if (root->right && getBalance(root->right) > 0) {
            // right-left problem
            root->right = rotateRight(root->right);
        }
        root = rotateLeft(root);
    }
}

void AVL::draw() {
    initializeAnimation();
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
                DrawLineEx(pointNode, pointLeft, 2.0, Node->left->color);
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
                DrawLineEx(pointNode, pointRight, 2.0, Node->right->color);
            }
            DrawCircle(Node->position.x, Node->position.y, Node->radius, Node->color);
            string s = to_string(Node->val);
            int textSize = MeasureText(s.c_str(), Node->radius);
            DrawText(s.c_str(), Node->position.x - textSize / 2, Node->position.y - Node->radius / 2, Node->radius, WHITE);
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
    set<int> st;
    while(st.size() < n) {
        int num = dist(gen);
        if (st.insert(num).second) {
            insertNode(TreeRoot, nullptr, num);
        }
    }
    setTreeSize(TreeRoot, 0);
}

void AVL::moveTree(TreeNode *&root, bool direction) {
    if (!root) return;
    root->position.x += (direction ? distance_x : -distance_x);
    moveTree(root->left, direction);
    moveTree(root->right, direction);
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

void AVL::setTreeSize(TreeNode*& root, float radius) {
    if(!root) return;
    root->setRadius(radius);
    setTreeSize(root->left, radius);
    setTreeSize(root->right, radius);
}

void AVL::initializeAnimation() {
    if(TreeRoot && TreeRoot->radius < 20) {
        float newRadius = min(TreeRoot->radius + (float)0.5 * 1.f, 20 * 1.f);
        setTreeSize(TreeRoot, newRadius);
        distance_x = TreeRoot->radius * 1.25 * 1.f;
        distance_y = TreeRoot->radius * 2 * 1.f;
        updateTreePosition();
    }
}