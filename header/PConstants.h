#pragma once
#include <raylib.h>
namespace PConstants {
    namespace PTitleBar {
        // Position
        const Vector2 pos = {0, 0};

        // Size
        const Vector2 size = {1200, 83};
        const int outlineThickness = 6;

        // Text size
        const int textSize = 30;

        // Color
        const Color boxColor = {248, 240, 240, 255};
        const Color outlineColor(BLACK);
    };

    namespace PFunctionArea {
        // Position
        const Vector2 pos = {0, 86};

        // Size
        const Vector2 size = {307, 296};
        const int boxHeight = 45;
        const int boxWidth = 143;
        const float boxHalfWidth = 146;
        const int boxOutlineThickness = 2;

        // Text size
        const int textSize = 20;

        // Space
        const float spaceX = 5.f;
        const float spaceY = 5.f;

        // Color
        const Color regionColor = {75, 189, 224, 255};
        const Color boxColor = WHITE;
        const Color iconBoxColor = {238, 238, 238, 255}; // Light gray
        const Color outlineBoxColor = BLACK;
        const Color GOColor = RED;
    };

    namespace PStepByStepMenu {
        // Position
        const Vector2 pos = {0, 387};
        const Vector2 skipBackwardCenter = {53, 34};
        const Vector2 undoCenter = {103, 34};
        const Vector2 playCenter = {153, 34};
        const Vector2 redoCenter = {203, 34};
        const Vector2 skipForwardCenter = {253, 34};

        // Size
        const Vector2 size = {307, 69};
        const float iconHeight = 25.f;
        const float iconWidth = 25.f;

        // Color
        const Color regionColor = {120, 209, 210, 255};
    };

    namespace PExplanationArea {
        // Position 
        const Vector2 pos = {0, 461};

        // Size
        const Vector2 size = {500, 65};

        // Color
        const Color backgroundColor = {151, 219, 174, 255};

        // Space 
        const float spaceX = 5.f;
        const float spaceY = 5.f;

        // Text
        const float fontSize = 20.f;
        const Color textColor = BLACK;
    };
    namespace PseudoCodeArea {
        // Pos
        const Vector2 pos = {0, 522.8};

        // Size
        const Vector2 size = {500, 278.2};

        //Color
        const Color backgroundColor = {205, 228, 173, 255};
        const Color highlightCodeColor = {235, 147, 93, 255};

        // Space 
        const float spaceX = 5.f;
        const float spaceY = 5.f;

        // Text
        const float fontSize = 20.f;
        const Color textColor = BLACK;

    }

    namespace PSwitchBox {
        // Size
        const float arrowHeadWidth = 22.f;
        const float arrowHeadHeight = 12.5f;

        // Space
        const float arrowHeadSpace = 10.f;

        // Color
        const Color arrowColor1 = BLACK;
        const Color arrowColor2 = {150, 150, 150, 255};
        // Text
        const float fontSize = 20.f;
        const Color textColor = BLACK;
    };

    namespace PInputBox {
        // Color
        const Color titleColor = {150, 150, 150, 255};
        const Color inputColor = BLACK;
    };

    namespace PBOX {
        // Size
        const float emphasizeThickness = 0.5f;
    };

    namespace PCursor {
        // Size
        const int height = 20;
        const int width = 8;
        
        // Space
        const int leftSpace = 5;

        // Time
        const float fullTime = 0.8f;
        const float onTime = 0.4f;
    };

    namespace PLimit {
        const int intData = (int)1e9;
        const int maxInputLength = 9;
    };

    namespace PIconBox {
        const float height = 41;
        const float width = 139;
    };

    namespace DS1 {
        // Movement
        const float speed = 600.f;

        // Position
        const Vector2 headPosition = {400, 200};
    };

    namespace PNode {
        // Node radius
        const float innerRadius = 20.f; // Radius of content region
        const float outerRadius = 23.f; // Radius of the whole node

        // Size
        const float characterSize = 20.f; // Font size of content
        const float informationSize = 20.f;
        const float lineThickness = 3.f; // Thickness of the line connecting nodes
        const float lineLength = 100.f; // Length of the line connecting nodes

        // Space
        const float textSpace = 5.f; // Space between text informing the node and the node
        const float newNodeSpace = 40.f; // Space between the added node in animation

        // Arrow head
        const float arrowWidth = 12.f;
        const float arrowHeight = 8.f;

        // Color
        const Color innerColor = WHITE;
        const Color outerColor = BLACK;
        const Color textColor = BLACK;

        const Color innerHighlightColor = {255, 138, 39, 255};
        const Color outerHighlightColor = {255, 138, 39, 255};
        const Color textHighlightColor = WHITE;

        const Color informationTextColor = BLACK;
    }

    namespace PNodeLine {
        const Color color = BLACK;
        const Color highlightColor = {255, 138, 39, 255};
    }

    namespace PAnimation
    {
        // Time
        const float waitTime = 1.0f;
    }

};
