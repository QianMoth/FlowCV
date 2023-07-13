#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>

#include "drawing.h"

namespace ax::Widgets {

using Drawing::IconType;

///@brief icon
///
///@param size
///@param nodeSize
///@param type
///@param filled
///@param color 颜色
///@param innerColor
///@param isInput
void Icon(const ImVec2 &size, const ImRect &nodeSize, IconType type, bool filled,
          const ImVec4 &color = ImVec4(1, 1, 1, 1), const ImVec4 &innerColor = ImVec4(0, 0, 0, 0),
          bool isInput = false);

}  // namespace ax::Widgets