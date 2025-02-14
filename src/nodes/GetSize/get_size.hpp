//
// Plugin GetSize
//

#ifndef FLOWCV_PLUGIN_GET_SIZE_HPP_
#define FLOWCV_PLUGIN_GET_SIZE_HPP_
#include <DSPatch.h>

#include <nlohmann/json.hpp>

#include "Types.hpp"
#include "imgui_opencv.hpp"
#include "imgui_wrapper.hpp"

namespace DSPatch::DSPatchables {

class GetSize final : public Component
{
  public:
    GetSize();
    void UpdateGui(void *context, int interface) override;
    bool HasGui(int interface) override;
    std::string GetState() override;
    void SetState(std::string &&json_serialized) override;

  protected:
    void Process_(SignalBus const &inputs, SignalBus &outputs) override;

  private:
};

}  // namespace DSPatch::DSPatchables

#endif  // FLOWCV_PLUGIN_GET_SIZE_HPP_
