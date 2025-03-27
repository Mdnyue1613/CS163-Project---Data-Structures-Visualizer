#include"../header/AVL.h"

void AVL::drawTree() {
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


void AVL::initializeAnimation() {
    if(TreeRoot && TreeRoot->radius < 20) {
        float newRadius = min(TreeRoot->radius + (float)0.5 * 1.f, 20 * 1.f);
        setTreeSize(TreeRoot, newRadius);
        distance_x = TreeRoot->radius * 1.25 * 1.f;
        distance_y = TreeRoot->radius * 2 * 1.f;
        updateTreePosition();
    }
    else isInit = 0;
    drawTree();
}


void AVL::insertAnimation() {

}

void AVL::deleteAnimation() {

}

void AVL::findAnimation() {

}