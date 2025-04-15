#pragma once
#include "raylib.h"
#include <string>
#include <vector>

// --- Node structure for the Singly Linked List used in Hash Table Chaining ---
struct SinglyLinkedListNode {
    // --- Constants for Node Visualization (can be adjusted) ---
    const float SLL_NODE_INNER_RADIUS = 20.0f;
    const float SLL_NODE_OUTER_RADIUS = 25.0f;
    const int SLL_NODE_CHAR_SIZE = 20;
    const float SLL_NODE_LINE_THICKNESS = 2.0f;
    const float SLL_NODE_ARROW_WIDTH = 8.0f;
    const float SLL_NODE_ARROW_HEIGHT = 5.0f;
    const float SLL_CHAIN_SPACING_Y = 70.0f; // Vertical space between nodes in a chain
    const float SLL_CHAIN_SPACING_X = 0.0f; // Horizontal offset (can be non-zero)
    const float SLL_FADE_SPEED = 2.0f; // Speed for fading out
    int data;
    SinglyLinkedListNode *pNext;

    // --- Visual Properties ---
    Vector2 center = {0, 0};
    char label[11] = ""; // Max 10 digits for int + sign + null terminator
    int labelLength = 0;
    float innerRadius = SLL_NODE_INNER_RADIUS;
    float outerRadius = SLL_NODE_OUTER_RADIUS;
    int characterSize = SLL_NODE_CHAR_SIZE;
    float lineThickness = SLL_NODE_LINE_THICKNESS;
    float arrowWidth = SLL_NODE_ARROW_WIDTH;
    float arrowHeight = SLL_NODE_ARROW_HEIGHT;


    // --- Visualization State ---
    enum NodeState { NORMAL, HIGHLIGHT_CHECK, HIGHLIGHT_FOUND, HIGHLIGHT_INSERT, HIGHLIGHT_DELETE, FADING };
    NodeState vizState = NORMAL;
    Color vizColor = BLACK; // Color for text/outline based on state
    float vizScale = 1.0f;  // For fade/appear animations
    int tableIndex = -1;    // Which table slot this node belongs to (useful for layout)

    // --- Methods ---
    SinglyLinkedListNode(int val = 0); // Constructor
    void draw(void);                 // Draw the node and link to next
    void makeLabel(void);            // Convert data to string label
    void calculateChainPosition(SinglyLinkedListNode* prevNodeInChain, Vector2 tableSlotPos); // Position node in chain
    void updateAnimation(float deltaTime); // Update fade/appear animations
    void setHighlight(NodeState newState); // Helper to set color/state
};