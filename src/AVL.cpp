#include "../header/AVL.h"

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
    isInsert = isInit = isDelete = isFind = 0;
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
    Path.clear();
    insertNodeNonDuplicate(root, NULL, x);
    updateTreePosition();
}

void AVL::insertNodeNonDuplicate(TreeNode *&root, TreeNode *parent, int x) {
    if (!root) {
        root = new TreeNode(x);
        allNode.push_back(root);
        root->parent = parent;
        if (parent == nullptr) {
            root->position = {600, 400};
            root->targetPosition = {600, 400};
        } else {
            if (x < parent->val) {
                root->position = {parent->targetPosition.x - distance_x, parent->targetPosition.y + distance_y};
                root->isLeft = 1;
            } else {
                root->position = {parent->targetPosition.x + distance_x, parent->targetPosition.y + distance_y};
                root->isLeft = 0;
            }
        }
        root->setRadius(0);
        root->setColor(GREEN);
        NodeInsert = root;
        animationStep = 0;
        return;
    }
    Path.push_back(root);
    if (x < root->val) insertNodeNonDuplicate(root->left, root, x);
    else if (x > root->val) insertNodeNonDuplicate(root->right, root, x);

    setHeight(root);
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
    uniform_int_distribution<int> dist(1, 99);
    
    if(TreeRoot){
        removeAll();
    }
    set<int> st;
    while(st.size() < n) {
        int num = dist(gen);
        if (st.insert(num).second) {
            insertNodeWithNoAnimation(TreeRoot, nullptr, num);
        }
    }
    setTreeSize(TreeRoot, 0);
}

void AVL::moveTree(TreeNode *&root, bool direction) {
    if (!root) return;
    root->targetPosition.x += (direction ? distance_x : -distance_x);
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
            Node->targetPosition = {600, 400};
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
                    Node->targetPosition = {Node->parent->targetPosition.x + (Node->isLeft ? -distance_x : distance_x), Node->parent->targetPosition.y + distance_y};
                    break;
                }
            }
        }
    }
    if(NodeDelete && NodeDelete->left == nullptr && NodeDelete->right == nullptr && NodeDelete->parent == nullptr) allNode.push_back(NodeDelete);
}

void AVL::setTreeSize(TreeNode*& root, float radius) {
    if(!root) return;
    root->setRadius(radius);
    setTreeSize(root->left, radius);
    setTreeSize(root->right, radius);
}

void AVL::setCurrentPosition() {
    for (auto& Node : allNode) {
        Node->position.x = Node->position.x + (Node->targetPosition.x - Node->position.x) * animationProgress;
        Node->position.y = Node->position.y + (Node->targetPosition.y - Node->position.y) * animationProgress;
    }
}



void AVL::rotateNode(TreeNode*& root) {
    if(!root) return;
    TreeNode* p = root->parent;
    if (getBalance(root) > 1) {
        // imbalance to the left
            if (root->left && getBalance(root->left) < 0) {
                // left-right problem
                root->left = rotateLeft(root->left);
            }
            if(!p) {
                root = rotateRight(root);
                TreeRoot = root;
            }
            else {
                if (root->isLeft) {
                    p->left = rotateRight(root);
                }
                else {
                    p->right = rotateRight(root);
                }
            }
        }
        else if (getBalance(root) < -1) {
            // imbalance to the right
            if (root->right && getBalance(root->right) > 0) {
                // right-left problem
                root->right = rotateRight(root->right);
            }
            if (!p) {
                root = rotateLeft(root);
                TreeRoot = root;
            }
            else {
                if (root->isLeft) {
                    p->left = rotateLeft(root);
                }
                else {
                    p->right = rotateLeft(root);
                }
            }
        }
}

void AVL::checkRotateChildNode() {
    if(rotationNode) {
        if(getBalance(rotationNode) > 1 && getBalance(rotationNode->left) < 0) {
            childRotateNode = rotationNode->left;
            isNeedToRotateChild = true;
        }
        else if (getBalance(rotationNode) < -1 && getBalance(rotationNode->right) > 0) {
            childRotateNode = rotationNode->right;
            isNeedToRotateChild = true;
        }
    }
}

void AVL::rotateChildNode() {
    if(childRotateNode) {
        if (getBalance(childRotateNode) < 0) {
            rotationNode->left = rotateLeft(childRotateNode);
        }
        else if (getBalance(childRotateNode) > 0) {
            rotationNode->right = rotateRight(childRotateNode);
        }
        updateTreePosition();
        childRotateNode = nullptr;
    }
}

void AVL::insertNodeWithNoAnimation(TreeNode *&root, TreeNode *parent, int x) {
    if (!root) {
        root = new TreeNode(x);
        allNode.push_back(root);
        root->parent = parent;
        if (parent == nullptr) {
            root->position = {600, 400};
            root->targetPosition = {600, 400};
        } else {
            if (x < parent->val) {
                root->position = {parent->targetPosition.x - distance_x, parent->targetPosition.y + distance_y};
                root->isLeft = 1;
            } else {
                root->position = {parent->targetPosition.x + distance_x, parent->targetPosition.y + distance_y};
                root->isLeft = 0;
            }
        }
        return;
    }
    if (x < root->val) insertNodeWithNoAnimation(root->left, root, x);
    else if (x > root->val) insertNodeWithNoAnimation(root->right, root, x);

    setHeight(root);

    if(getBalance(root) > 1) {
        if(root->left && getBalance(root->left) < 0) root->left = rotateLeft(root->left);
        if(parent == nullptr) {
            TreeRoot = rotateRight(root);
        }
        else {
            if(root->isLeft) parent->left = rotateRight(root);
            else parent->right = rotateRight(root);
        }
    }
    else if (getBalance(root) < -1) {
        if(root->right && getBalance(root->right) > 0) root->right = rotateRight(root->right);
        if(parent == nullptr) {
            TreeRoot = rotateLeft(root);
        }
        else {
            if(root->isLeft) parent->left = rotateLeft(root);
            else parent->right = rotateLeft(root);
        }
    }
}

void AVL::FindDeleteNode(TreeNode*& root, TreeNode* parent, int x) {
    if(!root) {
        return;
    }
    Path.push_back(root);
    if (root->val == x) {
            NodeDelete = root;
            if(root->left && root->right) {
                FindNewDeleteNode(root->left);
            }
            isDelete = 1;
            return;
    }
    if(root->val < x) {
        FindDeleteNode(root->right, root, x);
    }
    else if(root->val > x) {
        FindDeleteNode(root->left, root, x);
    }
}

void AVL::FindNewDeleteNode(TreeNode*& root) {
    if(!root) return;
    Path.push_back(root);
    FindNewDeleteNode(root->right);
}

void AVL::prePareTreeForDelete() {
    if(NodeDelete) {
        TreeNode* parent = NodeDelete->parent;
        bool newChildState = NodeDelete->isLeft;
        if (NodeDelete->left) {
            TreeNode* newChild = NodeDelete->left;
            if(parent == nullptr) {
                TreeRoot = NodeDelete->left;
                TreeRoot->parent = nullptr;
            }
            else {
                if(NodeDelete->isLeft) parent->left = newChild;
                else parent->right = newChild;
                newChild->parent = parent;
            }
            newChild->isLeft = newChildState;
            // NodeDelete->targetPosition = newChild->position;
        }
        else if (NodeDelete->right) {
            TreeNode* newChild = NodeDelete->right;
            if(parent == nullptr) {
                TreeRoot = NodeDelete->right;
                TreeRoot->parent = nullptr;
            }
            else {
                if(NodeDelete->isLeft) parent->left = newChild;
                else parent->right = newChild;
                newChild->parent = parent;
            }
            newChild->isLeft = newChildState;
            // NodeDelete->targetPosition = newChild->position;
        }
        else {
            if(NodeDelete->isLeft) parent->left = nullptr;
            else parent->right = nullptr;
        }
        NodeDelete->parent = nullptr;
        NodeDelete->left = nullptr;
        NodeDelete->right = nullptr;
    }
    auto it = std::find(allNode.begin(), allNode.end(), NodeDelete);
    if (it != allNode.end()) allNode.erase(it);
}

void AVL::deleteNodeRunAtOnce(TreeNode*& root, TreeNode* parent, int x) {
    deleteWithNoAnimation(root, parent, x);
    updateTreePosition();
    setPositionImmediately();
}

void AVL::insertNodeRunAtOnce(TreeNode*& root, TreeNode* parent, int x) {
    insertNodeWithNoAnimation(root, parent, x);
    updateTreePosition();
    setPositionImmediately();
}

void AVL::deleteWithNoAnimation(TreeNode*& root, TreeNode* parent, int x) {
    if (!root) return;

    if (x < root->val) {
        deleteWithNoAnimation(root->left, root, x);
    } else if (x > root->val) {
        deleteWithNoAnimation(root->right, root, x);
    } else {
        // Tìm thấy node cần xóa
        if (root->left && root->right) {
            // Tìm node lớn nhất bên trái (tiền nhiệm)
            TreeNode* tmp = root->left;
            while (tmp->right) tmp = tmp->right;
            root->val = tmp->val; // copy giá trị
            deleteWithNoAnimation(root->left, root, tmp->val); // xóa node thay thế
        } else {
            // Một con hoặc không có con
            TreeNode* child = root->left ? root->left : root->right;
            bool stateChild = root->isLeft;
            delete root;
            root = child;
            if (root) {
                root->parent = parent;
                root->isLeft = stateChild;
            }
            return;
        }
    }

    // Cập nhật chiều cao & cân bằng lại
    setHeight(root);
    int balance = getBalance(root);

    if (balance > 1) {
        if (getBalance(root->left) < 0) root->left = rotateLeft(root->left);
        root = rotateRight(root);
    } else if (balance < -1) {
        if (getBalance(root->right) > 0) root->right = rotateRight(root->right);
        root = rotateLeft(root);
    }

    // Gán lại cho cha nếu cần
    if (parent == nullptr) {
        TreeRoot = root;
    } else {
        if (root->isLeft) parent->left = root;
        else parent->right = root;
    }
}


void AVL::rotateImbalanceNode() {
    
}

void AVL::updatePathAfterDelete() {
    Path.clear();
    for (auto Node : allNode) {
        if(Node->isHighlight) Path.push_back(Node);
    }
}

