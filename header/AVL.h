#pragma once
#include <raylib.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <random>
#include <chrono>
#include <thread>
#include <set>
#include <iostream>
#include"PExplanationArea.h"
#include"LPseudoCode.h"
#include"PTaskManagement.h"
#include"LTreeNode.h"
#include"PNotification.h"

using namespace std;

/*  data structure to copy the AVL when animaion is running:
    TreeRootVector: store all root state of tree
    rotationNodeVector: store all rotation node of all animation step
    childRotateNodeVector: store all child node of all animation step
    NodeInsertVector: store all node when animation is running
    NodeDeleteVector: store all node when animation is running
    selectionNodeVector: store all node when animation is running
    allNodeVector: store vector of all node in animation
    PathVector: store all path in animation
    indexOfDeleteNodeInPathVector: store index when animation is running
    findDataVector: store data which is searched when animation is running
    isInsertVector: store all insert node in animation
    isDeleteVector: store all delete node in animation
    isFindVector: store all find node in animation
    isInitVector: check if tree is initialized
    isNeedToFindAnotherDeleteNodeVector: store if need to find another delete node in animation
    isNeedToRotateVector: store if need to rotate node in animation
    isNeedToRotateChildVector: store if need to rotate child node in animation
    allNodeVector: store all node in animation
    PseudoCodeAreaVector: store all pseudo code in animation
    explanationAreaVector: store all explanation in animation
    animationStepVector: store all animation step in animation
    hightLightNodeIndexVector: store all highlight node in animation
*/
struct AVLAnimation {
    // Stacks
    vector<string> recordVersionStack;
    vector<pair<int *, int>> recordIntStack;
    vector<pair<bool *, bool>> recordBoolStack;
    vector<pair<string *, string>> recordStringStack;
    vector<pair<vector<Color> *, vector<Color>>> recordVectorColorStack;
    vector<pair<Color *, Color>> recordColorStack;
    vector<pair<float *, float>> recordFloatStack;
    vector<pair<TreeNode**, TreeNode*>> recordTreeNodePointerStack;
    vector<pair<vector<TreeNode*>*, vector<TreeNode*>>> recordTreeNodePointerVectorStack;
    vector<pair<Vector2*, Vector2>> recordVector2Stack;
    vector<TreeNode**> recordCreateNodeStack;
    vector<pair<vector<TreeNode**>*, vector<TreeNode**>>> recordTreeNodeRecursionStack;
    vector<pair<vector<bool>*, vector<bool>>> recordVectorBoolStack;

    // ID
    enum requestID {
        skipBackward,
        goBackward,
        play,
        goForward,
        skipForward,
        noRequest
    };

    // Reset
    void reset(void);

    // Record
    void recordVersion(void);
    void recordInt(int *p);
    void recordBool(bool *p);
    void recordString(string *p);
    void recordVectorColor(vector<Color> *p);
    void recordColor(Color *p);
    void recordFloat(float *p);
    void recordTreeNodePointer(TreeNode **p);
    void recordTreeNodePointerVector(vector<TreeNode*> *p);
    void recordVector2(Vector2 *p);
    void recordCreateNode(TreeNode **p);
    void recordTreeNodeRecursion(vector<TreeNode**> *p);
    void recordVectorBool(vector<bool> *p);

    // Undo
    bool undoVersion(int stepRequest);
    void undoInt(void);
    void undoBool(void);
    void undoString(void);
    void undoVectorColor(void);
    void undoColor(void);
    void undoFloat(void);
    void undoTreeNodePointer(void);
    void undoTreeNodePointerVector(void);
    void undoVector2(void);
    void undoCreateNode(void);
    void undoTreeNodeRecursion(void);
    void undoVectorBool(void);
};

struct AVL {
    TreeNode* TreeRoot;
    TreeNode* rotationNode = nullptr;
    TreeNode* NodeInsert = nullptr;
    TreeNode* childRotateNode = nullptr;
    TreeNode* NodeDelete = nullptr;
    TreeNode* newDeleteNode = nullptr;
    TreeNode* selectionNode = nullptr;
    int indexOfDeleteNodeInPath = 0;
    int findData;
    bool isInsert, isDelete, isFind, isInit;
    bool isNeedToFindAnotherDeleteNode = false;
    bool isNeedToRotate = false, isNeedToRotateChild = false;
    vector<TreeNode*> allNode, Path;
    Vector2 rootPosition = {750, 200};
    float distance_x;
    float distance_y;
    int animationStep = 0;
    int hightLightNodeIndex = 0;
    PExplanationArea explanationArea;
    LPseudoCode PseudoCodeArea;
    AVLAnimation animation;
    PTaskManagement taskManagement;
    PNotification notificationBox;
    bool waitRequest = true;

    enum requestID {
        noRequest,
        skipBackward,
        goBackward,
        play,
        goForward,
        skipForward
    };

    AVL();
    int getBalance(TreeNode *root);
    void setHeight(TreeNode *&root);
    void insertNode(TreeNode *&root, TreeNode *parent, int x);
    void insertNodeNonDuplicate(TreeNode *&root, TreeNode *parent, int x);
    TreeNode* rotateLeft(TreeNode* &root);
    TreeNode* rotateRight(TreeNode* &root);
    void removeAll();
    ~AVL();
    void random(int n);
    void vectorIntInit(vector<int> nums);
    void draw();
    void moveTree(TreeNode *&root, bool distance);
    void updateTreePosition();
    void setTreeSize(TreeNode*& root, float raidus);
    void initializeAnimation();
    void insertAnimation();
    bool insertAnimationV2(int val, int stepRequest, PTaskManagement * taskManagement);
    bool insertStep0(int val, int stepRequest, PTaskManagement * taskManagement);
    bool insertStep1(int val, int stepRequest, PTaskManagement * taskManagement);
    bool insertStep2(int val, int stepRequest, PTaskManagement * taskManagement);
    bool insertStep3(int val, int stepRequest, PTaskManagement * taskManagement);
    bool insertStep4(int val, int stepRequest, PTaskManagement * taskManagement);
    bool insertStep5(int val, int stepRequest, PTaskManagement * taskManagement);
    bool insertStep6(int val, int stepRequest, PTaskManagement * taskManagement);
    bool insertStep7(int val, int stepRequest, PTaskManagement * taskManagement);
    bool insertStep8(int val, int stepRequest, PTaskManagement * taskManagement);
    bool insertStep9(int val, int stepRequest, PTaskManagement * taskManagement);
    void deleteAnimation();
    void findAnimation();
    void drawTree();
    void setCurrentPosition(float speed);
    void checkRotation();
    void rotateNode(TreeNode*& root);
    void animateRotation();
    void appearNode();
    void disapearnode();
    void defaultTree();
    void hightLightNode();
    void rotateChildNode();
    void checkRotateChildNode();
    void rotateImbalanceNode();
    void setPositionImmediately();
    void insertNodeWithNoAnimation(TreeNode *&root, TreeNode *parent, int x);
    void deleteNodeRunAtOnce(TreeNode*& root, TreeNode* parent, int x);
    void deleteWithNoAnimation(TreeNode*& root, TreeNode* parent, int x);
    void FindDeleteNode(TreeNode*& root, TreeNode* parent, int x);
    void FindNewDeleteNode(TreeNode*& root);
    void prePareTreeForDelete();
    void updatePathAfterDelete();
    void updateHeightInPath();
    void insertNodeRunAtOnce(TreeNode *&root, TreeNode *parent, int x);
    void findNode(TreeNode*& root, int x);
    void pushAnimation(); // push all state of this to animation
    void popAnimation(); // pop all state of this from animation
    void clearAnimation(); // clear all state of this from animation
    void assignAnimation(int animationState); // assign all state of this to animation
    void runAllInsertStepBeforeAnimation(); // run all insert step before animation and push all state of this to animation
    void runAllDeleteStepBeforeAnimation(); // run all delete step before animation and push all state of this to animation
    void runAllFindStepBeforeAnimation(); // run all find step before animation and push all state of this to animation
};
