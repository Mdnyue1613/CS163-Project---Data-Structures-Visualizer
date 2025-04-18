#pragma once
#include <raylib.h>
#include <iostream>
using namespace std;

struct TreeNode{
    int val;
    int height;
    bool isLeft;
    bool isHighlight = 0;
    Vector2 position;
    Vector2 targetPosition;
    float radius;
    Color color;

    TreeNode *left, *right, *parent;

    TreeNode(int x);
    void setRadius(float radius);
    void setColor(Color color);
};