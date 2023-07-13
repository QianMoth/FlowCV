#include "drawing.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

void ax::Drawing::DrawIcon(ImDrawList *drawList, const ImVec2 &a, const ImVec2 &b, IconType type,
                           bool filled, ImU32 color, ImU32 innerColor)
{
    auto rect = ImRect(a, b);
    auto rect_x = rect.Min.x;
    auto rect_y = rect.Min.y;
    auto rect_w = rect.Max.x - rect.Min.x;
    auto rect_h = rect.Max.y - rect.Min.y;
    auto rect_center_x = (rect.Min.x + rect.Max.x) * 0.5F;
    auto rect_center_y = (rect.Min.y + rect.Max.y) * 0.5F;
    auto rect_center = ImVec2(rect_center_x, rect_center_y);
    const auto outline_scale = rect_w / 24.0F;
    const auto extra_segments = static_cast<int>(2 * outline_scale);  // for full circle

    if (type == IconType::Flow) {
        const auto origin_scale = rect_w / 24.0F;

        const auto offset_x = 1.0F * origin_scale;
        const auto offset_y = 0.0F * origin_scale;
        const auto margin = (filled ? 2.0F : 2.0F) * origin_scale;
        const auto rounding = 0.1F * origin_scale;
        const auto tip_round = 0.7F;  // percentage of triangle edge (for tip)
        // const auto edge_round = 0.7F; // percentage of triangle edge (for corner)
        const auto canvas = ImRect(rect.Min.x + margin + offset_x, rect.Min.y + margin + offset_y,
                                   rect.Max.x - margin + offset_x, rect.Max.y - margin + offset_y);
        const auto canvas_x = canvas.Min.x;
        const auto canvas_y = canvas.Min.y;
        const auto canvas_w = canvas.Max.x - canvas.Min.x;
        const auto canvas_h = canvas.Max.y - canvas.Min.y;

        const auto left = canvas_x + canvas_w * 0.5F * 0.3F;
        const auto right = canvas_x + canvas_w - canvas_w * 0.5F * 0.3F;
        const auto top = canvas_y + canvas_h * 0.5F * 0.2F;
        const auto bottom = canvas_y + canvas_h - canvas_h * 0.5F * 0.2F;
        const auto center_y = (top + bottom) * 0.5F;
        // const auto angle = AX_PI * 0.5F * 0.5F * 0.5F;

        const auto tip_top = ImVec2(canvas_x + canvas_w * 0.5F, top);
        const auto tip_right = ImVec2(right, center_y);
        const auto tip_bottom = ImVec2(canvas_x + canvas_w * 0.5F, bottom);

        drawList->PathLineTo(ImVec2(left, top) + ImVec2(0, rounding));
        drawList->PathBezierCurveTo(ImVec2(left, top), ImVec2(left, top),
                                    ImVec2(left, top) + ImVec2(rounding, 0));
        drawList->PathLineTo(tip_top);
        drawList->PathLineTo(tip_top + (tip_right - tip_top) * tip_round);
        drawList->PathBezierCurveTo(tip_right, tip_right,
                                    tip_bottom + (tip_right - tip_bottom) * tip_round);
        drawList->PathLineTo(tip_bottom);
        drawList->PathLineTo(ImVec2(left, bottom) + ImVec2(rounding, 0));
        drawList->PathBezierCurveTo(ImVec2(left, bottom), ImVec2(left, bottom),
                                    ImVec2(left, bottom) - ImVec2(0, rounding));

        if (!filled) {
            if (innerColor & 0xFF000000) {
                drawList->AddConvexPolyFilled(drawList->_Path.Data, drawList->_Path.Size,
                                              innerColor);
            }

            drawList->PathStroke(color, true, 2.0F * outline_scale);
        } else {
            drawList->PathFillConvex(color);
        }
    } else {
        auto triangleStart = rect_center_x + 0.32F * rect_w;

        auto rect_offset = -static_cast<int>(rect_w * 0.25F * 0.25F);

        rect.Min.x += rect_offset;
        rect.Max.x += rect_offset;
        rect_x += rect_offset;
        rect_center_x += rect_offset * 0.5F;
        rect_center.x += rect_offset * 0.5F;

        if (type == IconType::Circle) {
            const auto c = rect_center;

            if (!filled) {
                const auto r = 0.5F * rect_w / 2.0F - 0.5F;

                if (innerColor & 0xFF000000) {
                    drawList->AddCircleFilled(c, r, innerColor, 12 + extra_segments);
                }
                drawList->AddCircle(c, r, color, 12 + extra_segments, 2.0F * outline_scale);
            } else {
                drawList->AddCircleFilled(c, 0.5F * rect_w / 2.0F, color, 12 + extra_segments);
            }
        }

        if (type == IconType::Square) {
            if (filled) {
                const auto r = 0.5F * rect_w / 2.0F;
                const auto p0 = rect_center - ImVec2(r, r);
                const auto p1 = rect_center + ImVec2(r, r);

                drawList->AddRectFilled(p0, p1, color, 0, 15 + extra_segments);
            } else {
                const auto r = 0.5F * rect_w / 2.0F - 0.5F;
                const auto p0 = rect_center - ImVec2(r, r);
                const auto p1 = rect_center + ImVec2(r, r);

                if (innerColor & 0xFF000000) {
                    drawList->AddRectFilled(p0, p1, innerColor, 0, 15 + extra_segments);
                }

                drawList->AddRect(p0, p1, color, 0, 15 + extra_segments, 2.0F * outline_scale);
            }
        }

        if (type == IconType::Grid) {
            const auto r = 0.5F * rect_w / 2.0F;
            const auto w = ceilf(r / 3.0F);

            const auto baseTl =
                ImVec2(floorf(rect_center_x - w * 2.5F), floorf(rect_center_y - w * 2.5F));
            const auto baseBr = ImVec2(floorf(baseTl.x + w), floorf(baseTl.y + w));

            auto tl = baseTl;
            auto br = baseBr;
            for (int i = 0; i < 3; ++i) {
                tl.x = baseTl.x;
                br.x = baseBr.x;
                drawList->AddRectFilled(tl, br, color);
                tl.x += w * 2;
                br.x += w * 2;
                if (i != 1 || filled) {
                    drawList->AddRectFilled(tl, br, color);
                }
                tl.x += w * 2;
                br.x += w * 2;
                drawList->AddRectFilled(tl, br, color);

                tl.y += w * 2;
                br.y += w * 2;
            }

            triangleStart = br.x + w + 1.0F / 24.0F * rect_w;
        }

        if (type == IconType::RoundSquare) {
            if (filled) {
                const auto r = 0.5F * rect_w / 2.0F;
                const auto cr = r * 0.5F;
                const auto p0 = rect_center - ImVec2(r, r);
                const auto p1 = rect_center + ImVec2(r, r);

                drawList->AddRectFilled(p0, p1, color, cr, 15);
            } else {
                const auto r = 0.5F * rect_w / 2.0F - 0.5F;
                const auto cr = r * 0.5F;
                const auto p0 = rect_center - ImVec2(r, r);
                const auto p1 = rect_center + ImVec2(r, r);

                if (innerColor & 0xFF000000) {
                    drawList->AddRectFilled(p0, p1, innerColor, cr, 15);
                }

                drawList->AddRect(p0, p1, color, cr, 15, 2.0F * outline_scale);
            }
        } else if (type == IconType::Diamond) {
            if (filled) {
                const auto r = 0.607F * rect_w / 2.0F;
                const auto c = rect_center;

                drawList->PathLineTo(c + ImVec2(0, -r));
                drawList->PathLineTo(c + ImVec2(r, 0));
                drawList->PathLineTo(c + ImVec2(0, r));
                drawList->PathLineTo(c + ImVec2(-r, 0));
                drawList->PathFillConvex(color);
            } else {
                const auto r = 0.607F * rect_w / 2.0F - 0.5F;
                const auto c = rect_center;

                drawList->PathLineTo(c + ImVec2(0, -r));
                drawList->PathLineTo(c + ImVec2(r, 0));
                drawList->PathLineTo(c + ImVec2(0, r));
                drawList->PathLineTo(c + ImVec2(-r, 0));

                if (innerColor & 0xFF000000) {
                    drawList->AddConvexPolyFilled(drawList->_Path.Data, drawList->_Path.Size,
                                                  innerColor);
                }

                drawList->PathStroke(color, true, 2.0F * outline_scale);
            }
        } else {
            const auto triangleTip = triangleStart + rect_w * (0.45F - 0.32F);

            drawList->AddTriangleFilled(ImVec2(ceilf(triangleTip), rect_y + rect_h * 0.5F),
                                        ImVec2(triangleStart, rect_center_y + 0.15F * rect_h),
                                        ImVec2(triangleStart, rect_center_y - 0.15F * rect_h),
                                        color);
        }
    }
}
