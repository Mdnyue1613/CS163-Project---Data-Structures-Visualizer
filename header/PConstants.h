#pragma once
#include <raylib.h>
struct PConstants {
    struct PTitleBar {
        // Position
        static Vector2 pos;
        // Size
        static Vector2 size;
        static int outlineThickness;
        // Text size
        static int textSize;
        // Color
        static Color boxColor;
        static Color outlineColor;
    };

    struct PFunctionArea {
        // Position
        static Vector2 pos;
        // Size
        static Vector2 size;
        static int boxHeight;
        static int boxWidth;
        static float boxHalfWidth;
        static int boxOutlineThickness;
        // Text size
        static int textSize;
        // Space
        static float spaceX;
        static float spaceY;
        // Color
        static Color regionColor;
        static Color boxColor;
        static Color iconBoxColor;
        static Color outlineBoxColor;
        static Color GOColor;
    };
    struct PStepByStepMenu {
        // Position
        static Vector2 pos;
        static Vector2 skipBackwardCenter;
        static Vector2 undoCenter;
        static Vector2 playCenter;
        static Vector2 redoCenter;
        static Vector2 skipForwardCenter;
        // Size
        static Vector2 size;
        static float iconHeight;
        static float iconWidth;
        // Color
        static Color regionColor;
    };

    struct PExplanationArea {
        // Position 
        static Vector2 pos;
        // Size
        static Vector2 size;
        // Color
        static Color backgroundColor;
        // Space 
        static float spaceX;
        static float spaceY;
        // Text
        static float fontSize;
        static Color textColor;
    };

    struct PseudoCodeArea {
        // Pos
        static Vector2 pos;
        // Size
        static Vector2 size;
        //Color
        static Color backgroundColor;
        static Color highlightCodeColor;
        // Space 
        static float spaceX;
        static float spaceY;
        // Text
        static float fontSize;
        static Color textColor;
    };

    struct PSwitchBox {
        // Size
        static float arrowHeadWidth;
        static float arrowHeadHeight;
        // Space
        static float arrowHeadSpace;
        // Color
        static Color arrowColor1;
        static Color arrowColor2;
        // Text
        static float fontSize;
        static Color textColor;
    };

    struct PInputBox {
        // Color
        static Color titleColor;
        static Color inputColor;
    };

    struct PCursor {
        static float leftSpace;
        static float fullTime;
        static float onTime;
    };

    struct PBOX {
        // Size
        static float emphasizeThickness;
    };

    struct PLimit {
        static int intData;
        static int maxInputLength;
    };

    struct PIconBox {
        static float height;
        static float width;
    };

    struct DS1 {
        // Movement
        static float speed;
        // Position
        static Vector2 headPosition;
        // Color
        static Color backgroundColor;
    };

    struct PNode {
        // Node radius
        static float innerRadius;
        static float outerRadius;
        // Size
        static float characterSize;
        static float informationSize;
        static float lineThickness;
        static float lineLength;
        // Space
        static float textSpace;
        static float newNodeSpace;
        // Arrow head
        static float arrowWidth;
        static float arrowHeight;
        // Color
        static Color innerColor;
        static Color outerColor;
        static Color textColor;
        static Color innerHighlightColor;
        static Color outerHighlightColor;
        static Color textHighlightColor;
        static Color informationTextColor;
    };

    struct PNodeLine {
        static Color color;
        static Color highlightColor;
    };

    struct PAnimation {
        // Time
        static float waitTime;
    };

};