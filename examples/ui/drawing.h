#pragma once
#include <imgui.h>

namespace ax::Drawing {

enum class IconType : ImU32
{
    Flow,
    Circle,
    Square,
    Grid,
    RoundSquare,
    Diamond
};

///@brief 绘制icon
///
///@param drawList
///@param a
///@param b
///@param type
///@param filled
///@param color
///@param innerColor
void DrawIcon(ImDrawList *drawList, const ImVec2 &a, const ImVec2 &b, IconType type, bool filled,
              ImU32 color, ImU32 innerColor);

}  // namespace ax::Drawing