//
// FlowCV Common Types
//

#ifndef FLOWCV_TYPES_HPP_
#define FLOWCV_TYPES_HPP_

namespace FlowCV
{

enum GuiInterfaceType
{
    GuiInterfaceType_Controls,
    GuiInterfaceType_Main,
    GuiInterfaceType_Other
};

///@brief 节点描述
///
struct NodeDescription
{
    int input_count{};
    int output_count{};
    std::string name{};
    DSPatch::Category category{};
    std::string author{};
    std::string version{};
};
}  // End Namespace FlowCV

namespace DSPatch
{
///@brief 获取目录
///
///@return const std::map<DSPatch::Category, const char *>&
const std::map<DSPatch::Category, const char *> &getCategories();
}  // namespace DSPatch

#endif  // FLOWCV_TYPES_HPP_
