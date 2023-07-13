//
// FlowCV Plugin Manager Class
//

#pragma once

#include <DSPatch.h>

#include <iostream>

#include "Types.hpp"

namespace FlowCV {

///@brief 插件信息
///
struct PluginInfo
{
    bool is_initialized = false;  // 初始化状态
    NodeDescription plugin_desc;
    DSPatch::Plugin *plugin_handle{};
};

///@brief 插件管理器
///
class PluginManager
{
  public:
    PluginManager() = default;
    ~PluginManager();

    ///@brief 根据插件路径加载插件
    ///
    ///@param plugin_path 插件完整路径
    ///@param recursive
    void LoadPlugins(const char *plugin_path, bool recursive = true);

    ///@brief  卸载插件
    ///
    void UnLoadPlugins();

    ///@brief 插件数量
    ///
    ///@return uint32_t
    uint32_t PluginCount();

    ///@brief 根据索引号获得插件描述
    ///
    ///@param index
    ///@param nodeDesc
    ///@return true
    ///@return false
    bool GetPluginDescription(uint32_t index, NodeDescription &nodeDesc);

    ///@brief 根据插件名字获取插件描述
    ///
    ///@param name
    ///@param nodeDesc
    ///@return true
    ///@return false
    bool GetPluginDescription(const char *name, NodeDescription &nodeDesc);

    ///@brief 实例化插件
    ///
    ///@param name
    ///@return std::shared_ptr<DSPatch::Component>
    std::shared_ptr<DSPatch::Component> CreatePluginInstance(const char *name);

    ///@brief 判断是否存在某个插件
    ///
    ///@param name 插件名称
    ///@return true
    ///@return false
    bool HasPlugin(const char *name);

  protected:
    ///@brief 在某个文件夹中扫描插件
    ///
    ///@param dir_path 文件夹路径
    ///@param recursive 递归搜索
    void ScanDirForPlugins(const char *dir_path, bool recursive = true);

  private:
    std::string plugin_path_;          // 插件所在文件夹路径
    std::vector<PluginInfo> plugins_;  // 存储插件信息
};
}  // End Namespace FlowCV
