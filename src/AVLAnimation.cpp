#include"../header/AVL.h"

void AVL::drawTree() {
    for (auto Node : allNode) {
        if(Node) {
                if (Node->left && Node->left->radius != 0) {
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
                if (Node->right && Node->right->radius != 0) {
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
        }
        DrawCircle(Node->position.x, Node->position.y, Node->radius, Node->color);
        string s = to_string(Node->val);
        int textSize = MeasureText(s.c_str(), Node->radius);
        if (Node->radius > 0) DrawText(s.c_str(), Node->position.x - textSize / 2, Node->position.y - Node->radius / 2, Node->radius, WHITE);
    }
}

void AVL::draw() {
    if(isInit == 1) {
        initializeAnimation();
    }

    else if (isInsert == 1) {
        insertAnimation();
    }

    else if (isDelete == 1) {
        deleteAnimation();
    }

    else if (isFind) {
        findAnimation();
    }

    else {
        drawTree();
    }
}


void AVL::initializeAnimation() {
    if(TreeRoot && TreeRoot->radius < 20) {
        float newRadius = min(TreeRoot->radius + (float)0.5 * 1.f, 20 * 1.f);
        setTreeSize(TreeRoot, newRadius);
        distance_x = TreeRoot->radius * 1.25 * 1.f;
        distance_y = TreeRoot->radius * 2 * 1.f;
        updateTreePosition();
        setPositionImmediately();
    }
    else isInit = 0;
    drawTree();
}


void AVL::insertAnimation() {
    animationProgress += 0.02f; // animation speed
    if (animationProgress >= 1.0f) {
        animationProgress = 0.0f;
        animationStep++;
    }

    switch (animationStep) {
    case 0: // Khởi tạo
        hightLightNode();
        break;

    case 1:
        if (NodeInsert) {
            setCurrentPosition();
            appearNode();
            drawTree();
        }
        break;

    case 2: 
        checkRotation();
        break;
    
    case 3:
        if (Path.empty() || isNeedToRotate) {
            WaitTime(0.5);
        }
        animationProgress = 0.0f;
        animationStep = 4;
        drawTree();
        break;
    
    case 4:
        if(isNeedToRotate == false) {
            animationStep = 6;
            animationProgress = 0.f;
        }
        else {
            checkRotateChildNode();
            if (isNeedToRotateChild == false) {
                animationStep = 5;
                animationProgress = 0.0f;
            }
            else if (childRotateNode != nullptr && isNeedToRotate == true) {
                rotateChildNode();
            }
        }
        if(isNeedToRotateChild) {
            setCurrentPosition();
        }
        drawTree();
        break;
    case 5:
        if(isNeedToRotate == false) {
            animationStep = 6;
            animationProgress = 0.f;
        }
        else {
            if(isNeedToRotate && rotationNode) {
                rotateNode(rotationNode);
                rotationNode = nullptr;
                updateTreePosition();
            }
        }
        if (isNeedToRotate) {
            setCurrentPosition();
        }
        drawTree();
        break;

    case 6:
        updateHeightInPath();
        break;

    default:
        for (auto Node : allNode) {
            Node->setColor(BLUE); 
        }
        isInsert = 0;
        hightLightNodeIndex = 0;
        Path.clear();
        NodeInsert = nullptr;
        isNeedToRotate = false;
        rotationNode = nullptr;
        animationStep = 0;
        drawTree();
        break;
    }
    drawTree();
}

void AVL::deleteAnimation() {
    animationProgress += 0.02;
    if (animationProgress >= 1.0f) {
        animationProgress = 0.0f;
        animationStep++;
    }
    switch (animationStep) {
    case 0:
        if (hightLightNodeIndex < Path.size()) {
            if(Path[hightLightNodeIndex] == NodeDelete) {
                Path[hightLightNodeIndex]->setColor(GREEN);
                indexOfDeleteNodeInPath = hightLightNodeIndex;
            }
            else {
                Path[hightLightNodeIndex]->setColor(YELLOW);
            }
            Path[hightLightNodeIndex]->isHighlight = true;
            hightLightNodeIndex++;
            drawTree();
            WaitTime(0.5);
        }
        break;

    case 1:
        if(NodeDelete) {
            if (NodeDelete->left && NodeDelete->right) {
                newDeleteNode = Path[hightLightNodeIndex - 1];
                swap(NodeDelete->val, newDeleteNode->val);
                NodeDelete->setColor(YELLOW);
                NodeDelete = newDeleteNode;
                newDeleteNode->setColor(GREEN);
                swap(Path[indexOfDeleteNodeInPath], Path[hightLightNodeIndex - 1]);
                WaitTime(0.5);
            }
            else {
                animationProgress = 0.0f;
                animationStep = 2;
            }
        }
        else {
            animationProgress = 0.0f;
            animationStep = 2;
        }
        break;

    case 2:
        prePareTreeForDelete();
        animationProgress = 0.0f;
        animationStep = 3;
        updateTreePosition();
        WaitTime(0.5);
        break;

    case 3:
        disapearnode();
        setCurrentPosition();
        break;

    case 4:
        while(true) {
            auto it = std::find(allNode.begin(), allNode.end(), NodeDelete);
            if (it != allNode.end()) allNode.erase(it);
            else break;
        }
        if(NodeDelete) {
            delete NodeDelete;
            NodeDelete = nullptr;
        }
        updatePathAfterDelete();
        hightLightNodeIndex = Path.empty() ? -1 : Path.size() - 1;
        animationProgress = 0.0f;
        animationStep = 5;
        break;

    case 5:
        for(int i = Path.size() - 1; i >= 0; i--) {
            setHeight(Path[i]);
        }
        animationProgress = 0.0f;
        animationStep = 6;
        break;

    case 6:
        checkRotation();
        break;

    case 7:
        if (Path.empty() || isNeedToRotate) {
            WaitTime(0.5);
        }
        animationProgress = 0.0f;
        animationStep = 8;
        drawTree();
        break;
    
    case 8:
        if(isNeedToRotate == false) {
            animationStep = 10;
            animationProgress = 0.f;
        }
        else {
            checkRotateChildNode();
            if (isNeedToRotateChild == false) {
                animationStep = 9;
                animationProgress = 0.0f;
            }
            else if (childRotateNode != nullptr && isNeedToRotate == true) {
                rotateChildNode();
            }
        }
        if(isNeedToRotateChild) {
            setCurrentPosition();
        }
        drawTree();
        break;
    case 9:
        if(isNeedToRotate == false) {
            animationStep = 10;
            animationProgress = 0.f;
        }
        else {
            if(isNeedToRotate && rotationNode) {
                rotateNode(rotationNode);
                rotationNode = nullptr;
                updateTreePosition();
            }
        }
        if (isNeedToRotate) {
            setCurrentPosition();
        }
        drawTree();
        break;

    case 10:
        updateHeightInPath();
        break;

    default:
        for (auto Node : allNode) {
            Node->setColor(BLUE); 
        }
        isDelete = 0;
        hightLightNodeIndex = 0;
        Path.clear();
        NodeDelete = nullptr;
        isNeedToRotate = false;
        rotationNode = nullptr;
        animationStep = 0;
        drawTree();
        break;
    }
    drawTree();
}

void AVL::findAnimation() {

}

void AVL::animateRotation() {
    if(isNeedToRotate == 1) {
        
    }
}

void AVL::appearNode() {
    if (NodeInsert) {
        float targetRadius = 20.0f;
        NodeInsert->radius = targetRadius * animationProgress;
        if(animationProgress >= 0.95) {
            NodeInsert->setColor(BLUE);
        }
    }
}

void AVL::defaultTree() {
    for (auto Node : allNode) {
        Node->setColor(BLUE);
        Node->isHighlight = false;
    }
}
void AVL::hightLightNode() {
    if (hightLightNodeIndex < Path.size()) {
        Path[hightLightNodeIndex]->setColor(YELLOW);
        Path[hightLightNodeIndex]->isHighlight = true;
        hightLightNodeIndex++;
        drawTree();
        WaitTime(0.5);
    }
}

void AVL::checkRotation() {
    if (hightLightNodeIndex >= Path.size()) hightLightNodeIndex = Path.size() - 1;
    if (isNeedToRotate == 1) {
        WaitTime(0.5);
        animationProgress = 0.f;
        animationStep++;
        return;
    }


    if (hightLightNodeIndex >= 0 && hightLightNodeIndex < Path.size()) {
        if (getBalance(Path[hightLightNodeIndex]) > 1 || getBalance(Path[hightLightNodeIndex]) < -1) {
            isNeedToRotate = 1;
            rotationNode = Path[hightLightNodeIndex];
            Path[hightLightNodeIndex]->isHighlight = false;
            Path[hightLightNodeIndex]->setColor(RED);
            drawTree();
            animationStep++;
        }
        else {
            Path[hightLightNodeIndex]->setColor(BLUE);
            Path[hightLightNodeIndex]->isHighlight = false;
            Path.pop_back();
            drawTree();
            if (hightLightNodeIndex <= 0) {
                animationStep++;
            }
            else {
                hightLightNodeIndex--;
            }
        }
        WaitTime(0.5);
    }

}

void AVL::setPositionImmediately() {
    for(auto Node : allNode) {
        Node->position = Node->targetPosition;
    }
}

void AVL::disapearnode() {
    if(NodeDelete) {
        NodeDelete->radius = NodeDelete->radius * (1 - animationProgress);
    }
}

void AVL::updateHeightInPath() {
    if(!Path.empty()) {
        setHeight(Path[hightLightNodeIndex]);
        Path[hightLightNodeIndex]->setColor(BLUE);
        WaitTime(0.5);
        hightLightNodeIndex--;
        Path.pop_back();
    }
}