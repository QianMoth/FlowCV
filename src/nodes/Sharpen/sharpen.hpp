//
// Plugin Sharpen
//

#ifndef FLOWCV_PLUGIN_SHARPEN_HPP_
#define FLOWCV_PLUGIN_SHARPEN_HPP_
#include <DSPatch.h>

#include <nlohmann/json.hpp>

#include "Properties.hpp"
#include "Types.hpp"
#include "imgui_opencv.hpp"
#include "imgui_wrapper.hpp"

namespace DSPatch::DSPatchables {

class Sharpen final : public Component
{
  public:
    Sharpen();
    void UpdateGui(void *context, int interface) override;
    bool HasGui(int interface) override;
    std::string GetState() override;
    void SetState(std::string &&json_serialized) override;

  protected:
    void Process_(SignalBus const &inputs, SignalBus &outputs) override;

  private:
    FlowCV::FlowCV_Properties props_;
};

}  // namespace DSPatch::DSPatchables

#endif  // FLOWCV_PLUGIN_SHARPEN_HPP_
