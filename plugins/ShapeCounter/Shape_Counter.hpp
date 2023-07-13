//
// Plugin ShapeCounter
//

#ifndef FLOWCV_PLUGIN_SHAPE_COUNTER_HPP_
#define FLOWCV_PLUGIN_SHAPE_COUNTER_HPP_
#include <DSPatch.h>

#include <FlowCV/Types.hpp>
#include <nlohmann/json.hpp>

#include "imgui_opencv.hpp"
#include "imgui_wrapper.hpp"

namespace DSPatch::DSPatchables {
namespace internal {
class ShapeCounter;
}

class DLLEXPORT ShapeCounter final : public Component
{
  public:
    ShapeCounter();
    void UpdateGui(void *context, int interface) override;
    bool HasGui(int interface) override;
    std::string GetState() override;
    void SetState(std::string &&json_serialized) override;

  protected:
    void Process_(SignalBus const &inputs, SignalBus &outputs) override;

  private:
    std::unique_ptr<internal::ShapeCounter> p;
    int counting_mode_;
    int size_threshold_;
    int size_match_;
    bool show_overlay_;
    cv::Point2i text_pos_;
    float text_scale_;
    ImVec4 text_color_;
    int text_thickness_;
    int text_font_;
};

EXPORT_PLUGIN(ShapeCounter)

}  // namespace DSPatch::DSPatchables

#endif  // FLOWCV_PLUGIN_SHAPE_COUNTER_HPP_
