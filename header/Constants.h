#pragma once
#include <raylib.h>
namespace Constants {
    namespace titleBar {
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

    namespace functionArea {
        // Position
        const Vector2 pos = {0, 86};

        // Size
        const Vector2 size = {307, 296};

        // Text size
        const int textSize = 20;

        // Color
        const Color boxColor = {75, 189, 224, 255};

    };
};