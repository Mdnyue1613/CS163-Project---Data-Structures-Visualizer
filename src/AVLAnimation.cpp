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
    /*
    * 0: highlight node in path
    * 1: appear node
    * 2: check rotation
    * 3: check child node rotation, if need to rotate child node, rotate child node
    * 4: roatae node which is need to rotate
    * 5: update height in path
    * 6: check rotation again and update height in path
    * 7: done algorithm
    */
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
        drawTree();
        break;
    }
    drawTree();
}

void AVL::insertAnimationV2() {
    /*
    * 0: highlight node in path
    * 1: appear node
    * 2: check rotation
    * 3: check child node rotation, if need to rotate child node, rotate child node
    * 4: roatae node which is need to rotate
    * 5: update height in path
    * 6: check rotation again and update height in path
    * 7: done algorithm
    */
    switch (animationStep) {
    case 0:
        animation.recordVersion();
        hightLightNode();
        if(hightLightNodeIndex - 1 >= 0 && NodeInsert) {
            animation.recordString(&explanationArea.content);
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
        if(hightLightNodeIndex >= Path.size()) {
            animation.recordInt(&hightLightNodeIndex);
            animationStep = 1;
        }
        break;

    case 1:
        animation.recordVersion();
        if(NodeInsert->radius < 0.001) WaitTime(0.5);
        if (NodeInsert) {
            animation.recordString(&explanationArea.content);
            explanationArea.update("root == NULL, root = new Node");

            setCurrentPosition(1);
            appearNode();
            animation.recordInt(&animationStep);
            animationStep = NodeInsert->radius >= 20.f ? 2 : 1;
            drawTree();
        }
        break;

    case 2: 
        checkRotation();
        if(Path.empty() || hightLightNodeIndex < 0 || isNeedToRotate) {
            animation.recordInt(&animationStep);
            animationStep = 3;
        }
        break;
    
    case 3:
        if (Path.empty() || isNeedToRotate) {
            WaitTime(0.5);
        }
        animation.recordInt(&animationStep);
        animationStep = 4;
        drawTree();
        break;
    
    case 4:
        if(isNeedToRotate == false) {
            animation.recordInt(&animationStep);
            animationStep = 6;
        }
        else {
            checkRotateChildNode();
            if (isNeedToRotateChild == false) {
                animation.recordInt(&animationStep);
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
        Node->isHighlight = false;
    }
        isInsert = 0;
        hightLightNodeIndex = 0;
        Path.clear();
        NodeInsert = nullptr;
        isNeedToRotate = false;
        rotationNode = nullptr;
        isNeedToRotateChild = false;
        childRotateNode = nullptr;
        selectionNode = nullptr;
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
        animation.recordFloat(&NodeInsert->radius);
        NodeInsert->radius = min(targetRadius, NodeInsert->radius + (float) 0.4);
        if(NodeInsert->radius >= targetRadius) {
            animation.recordColor(&NodeInsert->color);
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
        animation.recordColor(&Path[hightLightNodeIndex]->color);
        Path[hightLightNodeIndex]->setColor(YELLOW);
        animation.recordBool(&Path[hightLightNodeIndex]->isHighlight);
        Path[hightLightNodeIndex]->isHighlight = true;
        animation.recordInt(&hightLightNodeIndex);
        hightLightNodeIndex++;
        drawTree();
        WaitTime(0.5);
    }
}

void AVL::checkRotation() {

    if (hightLightNodeIndex >= Path.size()) {
        animation.recordInt(&hightLightNodeIndex);
        hightLightNodeIndex = Path.size() - 1;
    }
    if (isNeedToRotate == 1) {
        WaitTime(0.5);
        animation.recordInt(&animationStep);
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

void AVL::pushAnimation() {

    // animation.recordInt(&this->animationStep);
    // animation.animationStepVector.push_back(this->animationStep);
    // animation.recordInt(&this->hightLightNodeIndex);
    // animation.hightLightNodeIndexVector.push_back(this->hightLightNodeIndex);
    // animation.recordBool(&this->isNeedToRotate);
    // animation.isNeedToRotateVector.push_back(this->isNeedToRotate);
    // animation.recordBool(&this->isNeedToRotateChild);
    // animation.isNeedToRotateChildVector.push_back(this->isNeedToRotateChild);
    // animation.recordBool(&this->isInsert);
    // animation.isInsertVector.push_back(this->isInsert);
    // animation.recordBool(&this->isDelete);
    // animation.isDeleteVector.push_back(this->isDelete);
    // animation.recordBool(&this->isFind);
    // animation.isFindVector.push_back(this->isFind);
    // animation.recordBool(&this->isInit);
    // animation.isInitVector.push_back(this->isInit);
    // animation.recordBool(&this->isNeedToFindAnotherDeleteNode);
    // animation.isNeedToFindAnotherDeleteNodeVector.push_back(this->isNeedToFindAnotherDeleteNode);
    // animation.NodeDeleteVector.push_back(this->NodeDelete);
    // animation.selectionNodeVector.push_back(this->selectionNode);
    // animation.recordInt(&this->findData);
    // animation.findDataVector.push_back(this->findData);
    // animation.recordVectorColor(&this->PseudoCodeArea.codeLineColor);
    // animation.PseudoCodeAreaColorLineVector.push_back(this->PseudoCodeArea.codeLineColor);
    // animation.recordString(&this->explanationArea.content);
    // animation.explanationAreaVector.push_back(this->explanationArea.content);
    // animation.recordInt(&this->indexOfDeleteNodeInPath);
    // animation.indexOfDeleteNodeInPathVector.push_back(this->indexOfDeleteNodeInPath);
    // animation.allNodeVector.push_back(this->allNode);
    // animation.PathVector.push_back(this->Path);
    // animation.NodeInsertVector.push_back(this->NodeInsert);
    // animation.rotationNodeVector.push_back(this->rotationNode);
    // animation.childRotateNodeVector.push_back(this->childRotateNode);
    // animation.TreeRootVector.push_back(this->TreeRoot);
    // animation.newDeleteNodeVector.push_back(this->newDeleteNode);
}

void AVL::popAnimation() {
    if(animation.animationStepVector.size() > 0) {
        animation.animationStepVector.pop_back();
    }
    if(animation.hightLightNodeIndexVector.size() > 0) {
        animation.hightLightNodeIndexVector.pop_back();
    }
    if(animation.isNeedToRotateVector.size() > 0) {
        animation.isNeedToRotateVector.pop_back();
    }
    if(animation.isNeedToRotateChildVector.size() > 0) {
        animation.isNeedToRotateChildVector.pop_back();
    }
    if(animation.isInsertVector.size() > 0) {
        animation.isInsertVector.pop_back();
    }
    if(animation.isDeleteVector.size() > 0) {
        animation.isDeleteVector.pop_back();
    }
    if(animation.isFindVector.size() > 0) {
        animation.isFindVector.pop_back();
    }
    if(animation.isInitVector.size() > 0) {
        animation.isInitVector.pop_back();
    }
    if(animation.isNeedToFindAnotherDeleteNodeVector.size() > 0) {
        animation.isNeedToFindAnotherDeleteNodeVector.pop_back();
    }
    if(animation.NodeDeleteVector.size() > 0) {
        animation.NodeDeleteVector.pop_back();
    }
    if(animation.selectionNodeVector.size() > 0) {
        animation.selectionNodeVector.pop_back();
    }
    if(animation.findDataVector.size() > 0) {
        animation.findDataVector.pop_back();
    }
    if(animation.PseudoCodeAreaColorLineVector.size() > 0) {
        animation.PseudoCodeAreaColorLineVector.pop_back();
    }
    if(animation.explanationAreaVector.size() > 0) {
        animation.explanationAreaVector.pop_back();
    }
    if(animation.indexOfDeleteNodeInPathVector.size() > 0) {
        animation.indexOfDeleteNodeInPathVector.pop_back();
    }
    if(animation.allNodeVector.size() > 0) {
        animation.allNodeVector.pop_back();
    }
    if(animation.PathVector.size() > 0) {
        animation.PathVector.pop_back();
    }
    if(animation.NodeInsertVector.size() > 0) {
        animation.NodeInsertVector.pop_back();
    }
    if(animation.rotationNodeVector.size() > 0) {
        animation.rotationNodeVector.pop_back();
    }
    if(animation.childRotateNodeVector.size() > 0) {
        animation.childRotateNodeVector.pop_back();
    }
    if(animation.TreeRootVector.size() > 0) {
        animation.TreeRootVector.pop_back();
    }
    if(animation.newDeleteNodeVector.size() > 0) {
        animation.newDeleteNodeVector.pop_back();
    }
}

void AVL::clearAnimation() {
    animation.animationStepVector.clear();
    animation.hightLightNodeIndexVector.clear();
    animation.isNeedToRotateVector.clear();
    animation.isNeedToRotateChildVector.clear();
    animation.isInsertVector.clear();
    animation.isDeleteVector.clear();
    animation.isFindVector.clear();
    animation.isInitVector.clear();
    animation.isNeedToFindAnotherDeleteNodeVector.clear();
    animation.NodeDeleteVector.clear();
    animation.selectionNodeVector.clear();
    animation.findDataVector.clear();
    animation.PseudoCodeAreaColorLineVector.clear();
    animation.explanationAreaVector.clear();
    animation.indexOfDeleteNodeInPathVector.clear();
    animation.allNodeVector.clear();
    animation.PathVector.clear();
    animation.NodeInsertVector.clear();
    animation.rotationNodeVector.clear();
    animation.childRotateNodeVector.clear();
    animation.TreeRootVector.clear();
    animation.newDeleteNodeVector.clear();
}

void AVL::assignAnimation(int animationState) {
    if(animationState >= 0 && animationState < animation.animationStepVector.size()) {
        this->animationStep = animation.animationStepVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.hightLightNodeIndexVector.size()) {
        this->hightLightNodeIndex = animation.hightLightNodeIndexVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.isNeedToRotateVector.size()) {
        this->isNeedToRotate = animation.isNeedToRotateVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.isNeedToRotateChildVector.size()) {
        this->isNeedToRotateChild = animation.isNeedToRotateChildVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.isInsertVector.size()) {
        this->isInsert = animation.isInsertVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.isDeleteVector.size()) {
        this->isDelete = animation.isDeleteVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.isFindVector.size()) {
        this->isFind = animation.isFindVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.isInitVector.size()) {
        this->isInit = animation.isInitVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.isNeedToFindAnotherDeleteNodeVector.size()) {
        this->isNeedToFindAnotherDeleteNode = animation.isNeedToFindAnotherDeleteNodeVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.findDataVector.size()) {
        this->findData = animation.findDataVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.PseudoCodeAreaColorLineVector.size()) {
        this->PseudoCodeArea.codeLineColor = animation.PseudoCodeAreaColorLineVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.explanationAreaVector.size()) {
        this->explanationArea.content = animation.explanationAreaVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.indexOfDeleteNodeInPathVector.size()) {
        this->indexOfDeleteNodeInPath = animation.indexOfDeleteNodeInPathVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.allNodeVector.size()) {
        this->allNode = animation.allNodeVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.PathVector.size()) {
        this->Path = animation.PathVector[animationState];
    }
    
    if(animationState >= 0 && animationState < animation.NodeDeleteVector.size()) {
        this->NodeDelete = animation.NodeDeleteVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.selectionNodeVector.size()) {
        this->selectionNode = animation.selectionNodeVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.NodeInsertVector.size()) {
        this->NodeInsert = animation.NodeInsertVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.rotationNodeVector.size()) {
        this->rotationNode = animation.rotationNodeVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.childRotateNodeVector.size()) {
        this->childRotateNode = animation.childRotateNodeVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.TreeRootVector.size()) {
        this->TreeRoot = animation.TreeRootVector[animationState];
    }
    if(animationState >= 0 && animationState < animation.newDeleteNodeVector.size()) {
        this->newDeleteNode = animation.newDeleteNodeVector[animationState];
    }
}

void AVL::runAllInsertStepBeforeAnimation() {
    if(!NodeInsert) {
        return;
    }
    pushAnimation(); // Version 1.0
    animationStep = 0; // highlight node in path
    for(int i = 0; i < Path.size(); i++) {
        hightLightNodeIndex++;
        Path[i]->setColor(YELLOW);
        Path[i]->isHighlight = true;
        if(NodeInsert) {
            if(Path[i]->val < NodeInsert->val) {
                explanationArea.update("root->val < data, root = root->right");
            }
            else if(Path[i]->val > NodeInsert->val) {
                explanationArea.update("root->val > data, root = root->left");
            }
            else {
                explanationArea.update("root->val == data, root was inserted");
            }
            pushAnimation();
        }
    }

    animationStep = 1; // update Tree When appear node
    if(NodeInsert) {
        NodeInsert->setRadius(20.f);
        NodeInsert->setColor(BLUE);
        setPositionImmediately();
        explanationArea.update("root == NULL, root = new Node");
        animationStep = 2;
        pushAnimation();
    }
    animationStep = 2; // check rotation
    for(int i = Path.size() - 1; i >= 0; i--) {
        setHeight(Path[i]);
        if(getBalance(Path[i]) > 1 || getBalance(Path[i]) < -1) {
            isNeedToRotate = 1;
            rotationNode = Path[i];
            Path[i]->isHighlight = false;
            Path[i]->setColor(RED);
            TreeNode* tmpNode = Path[i];
            if(getBalance(Path[i]) > 1) {
                explanationArea.update("The left branch is heavier.\nroot->getBalance > 1, is not ok");
                if(tmpNode->left) {
                    if(getBalance(tmpNode->left) < 0) {
                        PseudoCodeArea.update(3);
                    }
                    else PseudoCodeArea.update(1);
                }
            }
            else {
                explanationArea.update("The right branch is heavier.\nroot->getBalance < -1, is not ok");
                if(tmpNode->right) {
                    if (getBalance(tmpNode->right) > 0) {
                        PseudoCodeArea.update(4);
                    }
                    else PseudoCodeArea.update(2);
                }
            }
            animationStep = 3;
            pushAnimation();
            break;
        }
        else {
            int gb = getBalance(Path[i]);
            string s = "root->getBalance == " + to_string(gb) + " , is ok";
            PseudoCodeArea.update(5);
            explanationArea.update(s);
            Path[i]->setColor(BLUE);
            Path[i]->isHighlight = false;
            if(hightLightNodeIndex <= 0) {
                hightLightNodeIndex = 0;
                animationStep = 3;
            }
            else {
                hightLightNodeIndex--;
            }
            Path.pop_back();
            pushAnimation();
        }
    }

    animationStep = 3; // wait the program to check rotation
    animationStep = 4; // check child node rotation, if need to rotate child node, rotate child node
    if(isNeedToRotate) {
        checkRotateChildNode();
        if(isNeedToRotateChild && childRotateNode) {
            rotateChildNode();
            setPositionImmediately();
            animationStep = 5;
            pushAnimation();
        }
    }
    animationStep = 5; // rotate node which is need to rotate
    if(isNeedToRotate) {
        rotateNode(rotationNode);
        rotationNode = nullptr;
        updateTreePosition();
        setPositionImmediately();
        animationStep = 6;
        pushAnimation();
    }
    animationStep = 6; // update height in path
    for(int i = Path.size() - 1; i >= 0; i--) {
        setHeight(Path[i]);
        int gb = getBalance(Path[i]);
        string s = "root->getBalance == " + to_string(gb) + " , is ok";
        explanationArea.update(s);
        PseudoCodeArea.update(5);
        Path[i]->setColor(BLUE);
        Path[i]->isHighlight = false;
        Path.pop_back();
        if(hightLightNodeIndex <= 0) {
            hightLightNodeIndex = 0;
            animationStep = 7;
        }
        else {
            hightLightNodeIndex--;
        }
        pushAnimation();
    }
    animationStep = 7; // done animation
    for (auto Node : allNode) {
        Node->setColor(BLUE);
        Node->isHighlight = false;
    }
    isInsert = 0;
    hightLightNodeIndex = 0;
    Path.clear();
    NodeInsert = nullptr;
    isNeedToRotate = false;
    rotationNode = nullptr;
    isNeedToRotateChild = false;
    childRotateNode = nullptr;
    selectionNode = nullptr;
    explanationArea.update("");
    PseudoCodeArea.update(-1);
    pushAnimation();
}