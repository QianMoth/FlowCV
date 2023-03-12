//
// Plugin DrawShapes
//

#include "Draw_Shapes.hpp"

using namespace DSPatch;
using namespace DSPatchables;
using namespace nlohmann;

static int32_t global_inst_counter = 0;

static const char *SHAPES[] = {"line", "circle", "rectangle"};

namespace DSPatch::DSPatchables
{

DrawShapes::DrawShapes() : Component(ProcessOrder::OutOfOrder), shapes_(json::array())
{
    // Name and Category
    SetComponentName_("Draw_Shapes");
    SetComponentCategory_(DSPatch::Category::Category_Draw);
    SetComponentAuthor_("Moth");
    SetComponentVersion_("0.1.0");
    SetInstanceCount(global_inst_counter);
    global_inst_counter++;

    // 1 inputs
    SetInputCount_(1, {"in"}, {IoType::Io_Type_CvMat});

    // 1 outputs
    SetOutputCount_(1, {"out"}, {IoType::Io_Type_CvMat});

    shapes_.clear();

    SetEnabled(true);
}

void DrawShapes::Process_(SignalBus const &inputs, SignalBus &outputs)
{
    // Input 1 Handler
    auto in1 = inputs.GetValue<cv::Mat>(0);
    if (!in1) {
        return;
    }

    if (!in1->empty()) {
        if (IsEnabled()) {
            cv::Mat frame;
            in1->copyTo(frame);

            for (const auto s : shapes_) {
                std::string type = s["type"].get<std::string>();
                if (type == "line") {
                    cv::line(frame,  // line
                        {s["pos1"]["x"].get<int>(), s["pos1"]["y"].get<int>()}, {s["pos2"]["x"].get<int>(), s["pos2"]["y"].get<int>()},
                        cv::Scalar(s["color"]["B"].get<float>() * 255, s["color"]["G"].get<float>() * 255, s["color"]["R"].get<float>() * 255),
                        s["thickness"].get<int>());
                }
                else if (type == "circle") {
                    cv::circle(frame,  // circle
                        {s["center"]["x"].get<int>(), s["center"]["y"].get<int>()}, s["radius"].get<int>(),
                        cv::Scalar(s["color"]["B"].get<float>() * 255, s["color"]["G"].get<float>() * 255, s["color"]["R"].get<float>() * 255),
                        s["thickness"].get<int>());
                }
                else if (type == "rectangle") {
                    cv::rectangle(frame,  // rectangle
                        {s["pos1"]["x"].get<int>(), s["pos1"]["y"].get<int>()}, {s["pos2"]["x"].get<int>(), s["pos2"]["y"].get<int>()},
                        cv::Scalar(s["color"]["B"].get<float>() * 255, s["color"]["G"].get<float>() * 255, s["color"]["R"].get<float>() * 255),
                        s["thickness"].get<int>());
                }
            }

            if (!frame.empty())
                outputs.SetValue(0, frame);
        }
        else {
            outputs.SetValue(0, *in1);
        }
    }
}

bool DrawShapes::HasGui(int interface)
{
    // This is where you tell the system if your node has any of the following
    // interfaces: Main, Control or Other
    if (interface == (int)FlowCV::GuiInterfaceType_Controls) {
        return true;
    }

    return false;
}

void DrawShapes::UpdateGui(void *context, int interface)
{
    auto *imCurContext = (ImGuiContext *)context;
    ImGui::SetCurrentContext(imCurContext);

    static int selected = 0;

    // When Creating Strings for Controls use: CreateControlString("Text Here",
    // GetInstanceName()).c_str() This will ensure a unique control name for
    // ImGui with multiple instance of the Plugin
    if (interface == (int)FlowCV::GuiInterfaceType_Controls) {
        int dataHeight = 22 * shapes_.size();
        if (dataHeight < 66)
            dataHeight = 66;
        if (dataHeight > 200)
            dataHeight = 200;
        ImGui::BeginChild(CreateControlString("Table", GetInstanceName()).c_str(), ImVec2(0, dataHeight), true, ImGuiWindowFlags_None);

        int i = 0;
        for (const auto &s : shapes_) {
            std::string type = s["type"].get<std::string>();
            if (ImGui::Selectable(CreateControlString(type.c_str(), std::to_string(i).c_str()).c_str(), i == selected, ImGuiSelectableFlags_None)) {
                selected = i;
            }
            i++;
        }
        ImGui::EndChild();

        static int current_shape = 0;
        ImGui::Combo(" ", &current_shape, SHAPES, IM_ARRAYSIZE(SHAPES));

        ImGui::SameLine();

        if (ImGui::Button("Add")) {
            json shape{{"type", std::string(SHAPES[current_shape])}, {"color", {{"R", 1.0f}, {"G", 1.0f}, {"B", 1.0f}}}, {"thickness", 1}};
            switch (current_shape) {
                case 0:
                case 2: {
                    shape["pos1"] = {{"x", 0}, {"y", 0}};
                    shape["pos2"] = {{"x", 0}, {"y", 0}};
                    break;
                }
                case 1: {
                    shape["center"] = {{"x", 0}, {"y", 0}};
                    shape["radius"] = 0;
                    break;
                }

                default:
                    break;
            }
            shapes_.push_back(shape);
        }

        ImGui::SameLine();

        if (ImGui::Button("Delete")) {
            if (shapes_.size() > selected) {
                shapes_.erase(shapes_.begin() + selected);
                if (shapes_.size() == selected)
                    selected -= 1;
            }
        }

        if (shapes_.size() > 0) {
            ImGui::Separator();

            json &s = shapes_.at(selected);
            std::string type = s["type"].get<std::string>();
            if (type == "line" || type == "rectangle") {
                ImGui::Text("Position:");
                ImGui::SetNextItemWidth(80);
                ImGui::DragInt(CreateControlString("X1", GetInstanceName()).c_str(), &(int &)s["pos1"]["x"].get_ref<int64_t &>(), 0.5f);
                ImGui::SameLine();
                ImGui::SetNextItemWidth(80);
                ImGui::DragInt(CreateControlString("Y1", GetInstanceName()).c_str(), &(int &)s["pos1"]["y"].get_ref<int64_t &>(), 0.5f);
                ImGui::SetNextItemWidth(80);
                ImGui::DragInt(CreateControlString("X2", GetInstanceName()).c_str(), &(int &)s["pos2"]["x"].get_ref<int64_t &>(), 0.5f);
                ImGui::SameLine();
                ImGui::SetNextItemWidth(80);
                ImGui::DragInt(CreateControlString("Y2", GetInstanceName()).c_str(), &(int &)s["pos2"]["y"].get_ref<int64_t &>(), 0.5f);
            }
            else if (type == "circle") {
                ImGui::Text("Center:");
                ImGui::SetNextItemWidth(80);
                ImGui::DragInt(CreateControlString("x", GetInstanceName()).c_str(), &(int &)s["center"]["x"].get_ref<int64_t &>(), 0.5f);
                ImGui::SameLine();
                ImGui::SetNextItemWidth(80);
                ImGui::DragInt(CreateControlString("y", GetInstanceName()).c_str(), &(int &)s["center"]["y"].get_ref<int64_t &>(), 0.5f);

                ImGui::DragInt(CreateControlString("radius", GetInstanceName()).c_str(), &(int &)s["radius"].get_ref<int64_t &>(), 0.5f);
            }

            ImGui::Separator();

            ImGui::DragInt(CreateControlString("Thickness", GetInstanceName()).c_str(), &(int &)s["thickness"].get_ref<int64_t &>(), 0.1f, 0, 100);

            static ImVec4 color{1.0f, 1.0f, 1.0f, 1.0f};
            ImGui::ColorEdit3(CreateControlString("Color", GetInstanceName()).c_str(), (float *)&color);
            s["color"] = {{"R", color.x}, {"G", color.y}, {"B", color.z}};
        }
    }
}

std::string DrawShapes::GetState()
{
    std::string stateSerialized = shapes_.dump(4);

    return stateSerialized;
}

void DrawShapes::SetState(std::string &&json_serialized)
{
    shapes_ = json::parse(json_serialized);
}

}  // End Namespace DSPatch::DSPatchables