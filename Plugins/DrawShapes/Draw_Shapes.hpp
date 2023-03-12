//
// Plugin DrawShapes
//

#ifndef FLOWCV_PLUGIN_DRAW_SHAPES_HPP_
#define FLOWCV_PLUGIN_DRAW_SHAPES_HPP_
#include <DSPatch.h>

#include "FlowCV_Types.hpp"
#include "imgui_opencv.hpp"
#include "imgui_wrapper.hpp"
#include "json.hpp"

namespace DSPatch::DSPatchables
{

class DrawShapes final : public Component
{
  public:
    DrawShapes();
    void UpdateGui(void *context, int interface) override;
    bool HasGui(int interface) override;
    std::string GetState() override;
    void SetState(std::string &&json_serialized) override;

  protected:
    void Process_(SignalBus const &inputs, SignalBus &outputs) override;

  private:
    nlohmann::json shapes_;
};

EXPORT_PLUGIN(DrawShapes)

}  // namespace DSPatch::DSPatchables

#endif  // FLOWCV_PLUGIN_DRAW_SHAPES_HPP_
