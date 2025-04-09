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

    namespace PSwitchBox {
        // Size
        const float arrowHeadWidth = 22.f;
        const float arrowHeadHeight = 12.5f;

        // Space
        const float arrowHeadSpace = 10.f;

        // Color
        const Color arrowColor1 = BLACK;
        const Color arrowColor2 = {150, 150, 150, 255};
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
    };

    namespace PIconBox {
        const float height = 41;
        const float width = 139;
    };

    namespace DS1 {
        const float speed = 400.f;
    };

    namespace PNode {
        const float innerRadius = 20.f; // Radius of content region
        const float outerRadius = 23.f; // Radius of the whole node
        const float characterSize = 20.f; // Font size of content
        const float lineThickness = 3.f; // Thickness of the line connecting nodes
        const float lineLength = 100.f; // Length of the line connecting nodes

        const float arrowWidth = 12.f;
        const float arrowHeight = 8.f;
    }
};
