#include "../header/LTreeNode.h"

TreeNode::TreeNode(int x) {
    val = x;
    parent = left = right = nullptr;
    height = 1;
    radius = 20;
    color = BLUE;
    position= {0, 0};
    targetPosition = {0, 0};
}

void TreeNode::setRadius(float radius) {
    this->radius = radius;
}

void TreeNode::setColor(Color color) {
    this->color = color;
}