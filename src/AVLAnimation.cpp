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
    explanationArea.draw();
    PseudoCodeArea.draw();
}


void AVL::initializeAnimation() {
    for(auto Node : allNode) {
        float deltaX = abs(Node->targetPosition.x - Node->position.x);
        float deltaY = abs(Node->targetPosition.y - Node->position.y);
        float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
        float cosAlpha = distance != 0 ? deltaX / distance : 1;
        float sinAlpha = distance != 0 ? deltaY / distance : 1;
        if(Node->position.x < Node->targetPosition.x) {
            Node->position.x = min(Node->position.x + 5.f * cosAlpha, Node->targetPosition.x);
        }
        else {
            Node->position.x = max(Node->position.x - 5.f * cosAlpha, Node->targetPosition.x);
        }
        if(Node->position.y < Node->targetPosition.y) {
            Node->position.y = min(Node->targetPosition.y, Node->position.y + 5.f * sinAlpha);
        }
        else {
            Node->position.y = max(Node->targetPosition.y, Node->position.y - 5.f * sinAlpha);
        }
    }
    int count = 0;
    for (auto Node : allNode) {
        if (Node->position.x != Node->targetPosition.x || Node->position.y != Node->targetPosition.y) break;
        else count++;
    }
    isInit = (count != allNode.size());
    drawTree();
}


void AVL::insertAnimation() {
    switch (animationStep) {
    case 0: 
        hightLightNode();
        if(hightLightNodeIndex - 1 >= 0 && NodeInsert) {
            if(Path[hightLightNodeIndex - 1]->val < NodeInsert->val) {
                explanationArea.update("root->val < data, root = root->right");
            }
            else if(Path[hightLightNodeIndex - 1]->val > NodeInsert->val) {
                explanationArea.update("root->val > data, root = root->left");
            }
            else {
                explanationArea.update("root->val == data, root was inserted");
            }
        }
        if(hightLightNodeIndex >= Path.size()) animationStep = 1;
        break;

    case 1:
        if(NodeInsert->radius < 0.001) WaitTime(0.5);
        if (NodeInsert) {
            explanationArea.update("root == NULL, root = new Node");
            setCurrentPosition(1);
            appearNode();
            animationStep = NodeInsert->radius >= 20.f ? 2 : 1;
            drawTree();
        }
        break;

    case 2: 
        checkRotation();
        if(Path.empty() || hightLightNodeIndex < 0) animationStep = 3;
        if(isNeedToRotate) animationStep = 3;
        break;
    
    case 3:
        if (Path.empty() || isNeedToRotate) {
            WaitTime(0.5);
        }
        animationStep = 4;
        drawTree();
        break;
    
    case 4:
        if(isNeedToRotate == false) {
            animationStep = 6;
        }
        else {
            checkRotateChildNode();
            if (isNeedToRotateChild == false) {
                animationStep = 5;
            }
            else if (childRotateNode != nullptr && isNeedToRotate == true) {
                rotateChildNode();
            }
        }
        if(isNeedToRotateChild) {
            setCurrentPosition(0.5);
        }
        drawTree();
        break;
    case 5:
        if(isNeedToRotate == false) {
            animationStep = 6;
        }
        else {
            if(isNeedToRotate && rotationNode) {
                rotateNode(rotationNode);
                rotationNode = nullptr;
                updateTreePosition();
            }
        }
        if (isNeedToRotate) {
            setCurrentPosition(0.5);
        }
        drawTree();
        break;

    case 6:
        updateHeightInPath();
        hightLightNodeIndex--;
        Path.pop_back();
        if(Path.empty() || hightLightNodeIndex < 0) animationStep = 7;
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
        selectionNode = nullptr;
        explanationArea.update("");
        PseudoCodeArea.update(-1);
        drawTree();
        break;
    }
    drawTree();
}


void AVL::deleteAnimation() {
    switch (animationStep) {
    case 0:
        if (hightLightNodeIndex < Path.size()) {
            if(Path[hightLightNodeIndex] == NodeDelete) {
                Path[hightLightNodeIndex]->setColor(GREEN);
                indexOfDeleteNodeInPath = hightLightNodeIndex;
                if(hightLightNodeIndex + 1 < Path.size()) isNeedToFindAnotherDeleteNode = true;
                if(isNeedToFindAnotherDeleteNode) {
                    explanationArea.update("root->val == data, both children are not NULL");
                }
                else {
                    explanationArea.update("root->val == data");
                }
            }
            else {
                Path[hightLightNodeIndex]->setColor(YELLOW);
                if(isNeedToFindAnotherDeleteNode) {
                    explanationArea.update("root->right != nullptr, root = root->right");
                }
                else {
                    if(Path[hightLightNodeIndex]->val < findData) {
                        explanationArea.update("root->val < data, root = root->right");
                    }
                    else if(Path[hightLightNodeIndex]->val > findData) {
                        explanationArea.update("root->val > data, root = root->left");
                    }
                }
            }
            Path[hightLightNodeIndex]->isHighlight = true;
            hightLightNodeIndex++;
            drawTree();
            WaitTime(0.5);
        }
        if(hightLightNodeIndex >= Path.size()) animationStep = 1;
        break;

    case 1:
        if (NodeDelete == nullptr) {
            animationStep = 11;
            explanationArea.update("data is not invalid in tree");
            WaitTime(0.5);
            break;
        }
        if(NodeDelete) {
            if (NodeDelete->left && NodeDelete->right) {
                newDeleteNode = Path[hightLightNodeIndex - 1];
                swap(NodeDelete->val, newDeleteNode->val);
                NodeDelete->setColor(YELLOW);
                NodeDelete = newDeleteNode;
                newDeleteNode->setColor(GREEN);
                swap(Path[indexOfDeleteNodeInPath], Path[hightLightNodeIndex - 1]);
                explanationArea.update("swap data of old target node and new target node");
                WaitTime(0.5);
            }
            else {
                animationStep = 2;
            }
        }
        animationStep = 2;
        break;

    case 2:
        prePareTreeForDelete();
        animationStep = 3;
        updateTreePosition();
        WaitTime(0.5);
        break;

    case 3:
        disapearnode();
        explanationArea.update("delete target node");
        setCurrentPosition(1);
        animationStep = NodeDelete->radius <= 0 ? 4 : 3;
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
        animationStep = 5;
        break;

    case 5:
        for(int i = Path.size() - 1; i >= 0; i--) {
            setHeight(Path[i]);
        }
        animationStep = 6;
        break;

    case 6:
        checkRotation();
        if(isNeedToRotate) animationStep = 7;
        if(Path.empty() || hightLightNodeIndex < 0) animationStep = 7;
        break;

    case 7:
        if (Path.empty() || isNeedToRotate) {
            WaitTime(0.5);
        }
        animationStep = 8;
        drawTree();
        break;
    
    case 8:
        if(isNeedToRotate == false) {
            animationStep = 10;
        }
        else {
            checkRotateChildNode();
            if (isNeedToRotateChild == false) {
                animationStep = 9;
            }
            else if (childRotateNode != nullptr && isNeedToRotate == true) {
                rotateChildNode();
            }
        }
        if(isNeedToRotateChild) {
            setCurrentPosition(0.5);
        }
        drawTree();
        break;
    case 9:
        if(isNeedToRotate == false) {
            animationStep = 10;
        }
        else {
            if(isNeedToRotate && rotationNode) {
                rotateNode(rotationNode);
                rotationNode = nullptr;
                updateTreePosition();
            }
        }
        if (isNeedToRotate) {
            setCurrentPosition(0.5);
        }
        drawTree();
        break;

    case 10:
        if(hightLightNodeIndex >= 0 && !Path.empty() && hightLightNodeIndex < Path.size()) {
            updateHeightInPath();
            if(getBalance(Path[hightLightNodeIndex]) > 1 || getBalance(Path[hightLightNodeIndex]) < -1) {
                isNeedToRotate = 1;
                rotationNode = Path[hightLightNodeIndex];
                Path[hightLightNodeIndex]->isHighlight = false;
                Path[hightLightNodeIndex]->setColor(RED);
                animationStep =  7;
                TreeNode* tmpNode = Path[hightLightNodeIndex];
                if(getBalance(Path[hightLightNodeIndex]) > 1) {
                    explanationArea.update("root->getBalance > 1, is not ok");
                    if(tmpNode->left) {
                        if(getBalance(tmpNode->left) < 0) {
                            PseudoCodeArea.update(3);
                        }
                        else {
                            PseudoCodeArea.update(1);
                        }
                    }
                }
                else {
                    explanationArea.update("root->getBalance < -1, is not ok");
                    if(tmpNode->right) {
                        if (getBalance(tmpNode->right) > 0) {
                            PseudoCodeArea.update(4);
                        }
                        else {
                            PseudoCodeArea.update(2);
                        }
                    }
                }
            }
            hightLightNodeIndex--;
            Path.pop_back();
            break;
        }
        else animationStep = 11;

    default:
        for (auto Node : allNode) {
            Node->setColor(BLUE); 
        }
        isDelete = 0;
        isNeedToFindAnotherDeleteNode = 0;
        hightLightNodeIndex = 0;
        Path.clear();
        NodeDelete = nullptr;
        isNeedToRotate = false;
        rotationNode = nullptr;
        selectionNode = nullptr;
        animationStep = 0;
        explanationArea.update("");
        PseudoCodeArea.update(-1);
        drawTree();
        break;
    }
    drawTree();
}

void AVL::findAnimation() {
    switch (animationStep) {
    case 0:
        hightLightNode();
        if(hightLightNodeIndex >= Path.size()) {
            animationStep = 1;
        }
        if(!Path.empty()) {
            if(Path[hightLightNodeIndex - 1]->val < findData) {
                explanationArea.update("root->val < data, root = root->right");
            }
            else if(Path[hightLightNodeIndex - 1]->val > findData) {
                explanationArea.update("root->val > data, root = root->left");
            }
            else {
                explanationArea.update("root->val == data. Data is valid in tree");
            }
        }
        break;
    case 1:
        WaitTime(0.5);
        if(selectionNode != nullptr) {
            selectionNode->setColor(DARKBLUE);
            explanationArea.update("root->val == data. Data is valid in tree");
        }
        else {
            explanationArea.update("root == NULL, data is invalid in tree");
        }
        animationStep = 2;
        break;
    case 2:
        WaitTime(0.5);
        defaultTree();
        if(selectionNode != nullptr) {
            selectionNode->setColor(DARKBLUE);
        }
        animationStep = 3;
        break;
    default:
        defaultTree();
        selectionNode = nullptr;
        isFind = 0;
        Path.clear();
        hightLightNodeIndex = 0;
        animationStep= 0;
        for(auto Node:allNode) {
            Node->isHighlight = 0;
        }
        break;
    }
    drawTree();
}

void AVL::animateRotation() {
    if(isNeedToRotate == 1) {
        
    }
}

void AVL::appearNode() {
    if (NodeInsert) {
        float targetRadius = 20.0f;
        NodeInsert->radius = min(targetRadius, NodeInsert->radius + (float) 0.4);
        if(NodeInsert->radius >= targetRadius) {
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
        animationStep++;
        return;
    }


    if (hightLightNodeIndex >= 0 && hightLightNodeIndex < Path.size()) {
        if (getBalance(Path[hightLightNodeIndex]) > 1 || getBalance(Path[hightLightNodeIndex]) < -1) {
            isNeedToRotate = 1;
            rotationNode = Path[hightLightNodeIndex];
            Path[hightLightNodeIndex]->isHighlight = false;
            Path[hightLightNodeIndex]->setColor(RED);
            TreeNode* tmpNode = Path[hightLightNodeIndex];
            if(getBalance(Path[hightLightNodeIndex]) > 1) {
                explanationArea.update("root->getBalance > 1, is not ok");
                if(tmpNode->left) {
                    if(getBalance(tmpNode->left) < 0) {
                        PseudoCodeArea.update(3);
                    }
                    else PseudoCodeArea.update(1);
                }
            }
            else {
                explanationArea.update("root->getBalance < -1, is not ok");
                if(tmpNode->right) {
                    if(getBalance(tmpNode->right) > 0) {
                        PseudoCodeArea.update(4);
                    }
                    else PseudoCodeArea.update(2);
                }
            }
            drawTree();
            animationStep++;
        }
        else {
            int gb = getBalance(Path[hightLightNodeIndex]);
            string s = "root->getBalance == " + to_string(gb) + " , is ok";
            PseudoCodeArea.update(5);
            explanationArea.update(s);
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
        NodeDelete->radius = max(0 * 1.f, NodeDelete->radius - (float) 0.4);
    }
}

void AVL::updateHeightInPath() {
    if(!Path.empty() && hightLightNodeIndex >= 0 && hightLightNodeIndex < Path.size()) {
        setHeight(Path[hightLightNodeIndex]);
        int gb = getBalance(Path[hightLightNodeIndex]);
        string s = "root->getBalance == " + to_string(gb) + " , is ok";
        explanationArea.update(s);
        PseudoCodeArea.update(5);
        Path[hightLightNodeIndex]->setColor(BLUE);
        WaitTime(0.5);
    }
}