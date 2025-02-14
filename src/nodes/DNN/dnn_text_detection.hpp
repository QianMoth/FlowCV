//
// Plugin DNN Text Detection
//

#ifndef FLOWCV_PLUGIN_DNN_TEXT_DETECTION_HPP_
#define FLOWCV_PLUGIN_DNN_TEXT_DETECTION_HPP_
#include <DSPatch.h>
#include <ImGuiFileBrowser.h>

#include <nlohmann/json.hpp>

#include "Types.hpp"
#include "dnn_backend_helper.hpp"
#include "imgui_opencv.hpp"
#include "imgui_wrapper.hpp"

namespace DSPatch::DSPatchables {
class TextDetection final : public Component
{
  public:
    TextDetection();
    void UpdateGui(void *context, int interface) override;
    bool HasGui(int interface) override;
    std::string GetState() override;
    void SetState(std::string &&json_serialized) override;

  protected:
    void Process_(SignalBus const &inputs, SignalBus &outputs) override;
    void InitDnn_();

  private:
    DnnBackendListHelper dnn_backend_helper_;
    bool is_initialized_{};
    bool pre_proc_resize_{};
    bool show_model_dialog_{};
    std::mutex io_mutex_;
    imgui_addons::ImGuiFileBrowser model_dialog_;
    std::string model_path_;
    std::vector<std::pair<std::string, cv::dnn::Backend>> backend_list_;
    std::vector<std::pair<std::string, cv::dnn::Target>> target_list_;
    int dnn_backend_idx_;
    cv::dnn::Backend current_backend_;
    int dnn_target_idx_;
    cv::dnn::Target current_target_;
    std::unique_ptr<cv::dnn::TextDetectionModel_DB> net_;
    ImVec4 bbox_color_;
    int bbox_thickness_;
    float mean_[3]{};
    float scale_;
    float bin_thresh_;
    float poly_thresh_;
    float unclip_ratio_;
    int max_candidates_;
    int model_res_[2]{};
    bool net_load_error{};
    bool needs_reinit_{};
    bool swap_rb_{};
    bool draw_detections_{};
};

}  // namespace DSPatch::DSPatchables

#endif  // FLOWCV_PLUGIN_DNN_TEXT_DETECTION_HPP_
