//
// Various OpenCV Blur Filters
//

#ifndef FLOWCV_BLUR_HPP_
#define FLOWCV_BLUR_HPP_
#include <DSPatch.h>

#include <nlohmann/json.hpp>

#include "Properties.hpp"
#include "Types.hpp"
#include "imgui_opencv.hpp"
#include "imgui_wrapper.hpp"

namespace DSPatch::DSPatchables {

class Blur final : public Component
{
  public:
    Blur();
    void UpdateGui(void *context, int interface) override;
    bool HasGui(int interface) override;
    std::string GetState() override;
    void SetState(std::string &&json_serialized) override;

  protected:
    void Process_(SignalBus const &inputs, SignalBus &outputs) override;

  private:
    std::mutex mutex_lock_;
    FlowCV::FlowCV_Properties props_;
};

}  // namespace DSPatch::DSPatchables

#endif  // FLOWCV_GAUSSIAN_BLUR_HPP_
