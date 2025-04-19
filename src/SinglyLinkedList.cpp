#include "../header/SinglyLinkedList.h"
#include <cmath> // For M_PI, cos, sin if needed for arrows
#include "raylib.h" 

// Constructor
SinglyLinkedListNode::SinglyLinkedListNode(int val) {
    data = val;
    pNext = nullptr;
    vizState = NORMAL;
    vizColor = BLACK;
    vizScale = 1.0f; // Start fully visible
    tableIndex = -1;
    makeLabel(); // Create label immediately
}

// Set Highlight State and Color
void SinglyLinkedListNode::setHighlight(NodeState newState) {
    vizState = newState;
    switch (newState) {
        case HIGHLIGHT_CHECK:   vizColor = BLUE; break;
        case HIGHLIGHT_FOUND:   vizColor = GREEN; break;
        case HIGHLIGHT_INSERT:  vizColor = DARKGREEN; break; // Or maybe a different appearing color
        case HIGHLIGHT_DELETE:  vizColor = RED; break;
        case FADING:            // Fading handled in updateAnimation, color might change too
        case NORMAL:
        default:                vizColor = BLACK; break;
    }
    if (newState != FADING) { // Reset scale unless fading
         vizScale = 1.0f;
         vizColor.a = 255;
    }
}

// Update Animation (primarily for fading)
void SinglyLinkedListNode::updateAnimation(float deltaTime) {
     if (vizState == FADING) {
        vizScale -= SLL_FADE_SPEED * deltaTime;
        if (vizScale < 0.0f) vizScale = 0.0f;
        vizColor.a = (unsigned char)(255.0f * vizScale); // Fade alpha
     } else {
         // Optional: Could add an appearing animation here if desired
         vizScale = 1.0f; // Ensure scale is 1 if not fading/appearing
         vizColor.a = 255;
     }
}

// Convert Data to Label String
void SinglyLinkedListNode::makeLabel(void) {
    labelLength = 0;
    int x = data;
    bool isNegative = false;

    if (x == 0) {
        label[labelLength++] = '0';
        label[labelLength] = '\0';
        return;
    }

    if (x < 0) {
        isNegative = true;
        x = -x; // Work with positive value
        // Check limits if necessary for INT_MIN
    }

    char tempLabel[11]; // Temporary buffer for reversing digits
    int tempLength = 0;
    do {
        if (tempLength < 10) { // Prevent buffer overflow
             tempLabel[tempLength++] = char(x % 10 + '0');
        } else {
            break; // Stop if number is too large
        }
        x /= 10;
    } while(x > 0);

    // Add sign if needed
    if (isNegative) {
        if (labelLength < 10) label[labelLength++] = '-';
    }

    // Reverse digits into the final label buffer
    for (int i = tempLength - 1; i >= 0; i--) {
        if (labelLength < 10) { // Prevent overflow on final copy
             label[labelLength++] = tempLabel[i];
        } else {
            break;
        }
    }
    label[labelLength] = '\0'; // Null-terminate the string
}


// Draw the Node
void SinglyLinkedListNode::draw(void) {
    if (vizScale <= 0.0f) return; // Don't draw if completely faded

    // Apply scaling and alpha
    float currentOuterRadius = outerRadius * vizScale;
    float currentInnerRadius = innerRadius * vizScale;
    int currentCharSize = (int)(characterSize * vizScale);
    Color currentColor = vizColor; // Base color set by setHighlight
    currentColor.a = (unsigned char)(255.0f * vizScale); // Apply alpha based on scale


    // Draw Node Ring
    DrawRing(center, currentInnerRadius, currentOuterRadius, 0, 360, 64, currentColor);

    // Draw Text (only if large enough)
    if (currentCharSize > 5) {
         int textWidth = MeasureText(label, currentCharSize);
         DrawText(label, center.x - textWidth / 2,
             center.y - currentCharSize / 2, currentCharSize, currentColor);
    }

    // Draw Link to NEXT node in the chain
    if(pNext && pNext->vizScale > 0.0f) {
        // Calculate arrow points based on current node center and next node center
        // Assumes vertical chain layout
        Vector2 startPos = {center.x, center.y + currentOuterRadius}; // Arrow starts from bottom
        Vector2 endPos = {pNext->center.x, pNext->center.y - pNext->outerRadius * pNext->vizScale}; // Arrow ends at top of next

        // Line connecting nodes
        DrawLineEx(startPos, endPos, lineThickness * vizScale, currentColor);

        // Draw Arrow Head at 'endPos' pointing downwards
        float arrowLength = arrowWidth * 1.5f; // Make arrow head proportional
        Vector2 arrowP1 = endPos;
        // Points relative to endPos, forming a downward triangle
        Vector2 arrowP2 = { endPos.x - arrowWidth * 0.7f * pNext->vizScale, endPos.y - arrowLength * pNext->vizScale };
        Vector2 arrowP3 = { endPos.x + arrowWidth * 0.7f * pNext->vizScale, endPos.y - arrowLength * pNext->vizScale };

        // Ensure arrow doesn't invert when scaled down too much
        if (pNext->vizScale > 0.1) {
             DrawTriangle(arrowP1, arrowP2, arrowP3, currentColor);
        }
    }
}

// Calculate Node Position in a Vertical Chain
void SinglyLinkedListNode::calculateChainPosition(SinglyLinkedListNode* prevNodeInChain, Vector2 tableSlotPos) {
    if (prevNodeInChain == nullptr) { // First node in chain
        // Position it below the table slot
        center = { tableSlotPos.x + SLL_CHAIN_SPACING_X, tableSlotPos.y + SLL_CHAIN_SPACING_Y };
    } else {
        // Position it below the previous node in the chain
        center = { prevNodeInChain->center.x + SLL_CHAIN_SPACING_X, prevNodeInChain->center.y + SLL_CHAIN_SPACING_Y };
    }
}