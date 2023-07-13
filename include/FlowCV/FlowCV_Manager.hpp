//
// FlowCV Manager
//

#pragma once

#include <DSPatch.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>

#include "Internal_Node_Manager.hpp"
#include "PluginManager.hpp"

namespace FlowCV {

///@brief 端口信息
///
struct IoInfo
{
    uint64_t id = 0;
    uint32_t index = 0;
};

///@brief 节点信息
///
struct NodeInfo
{
    uint64_t id;
    bool showControlUI;
    std::shared_ptr<DSPatch::Component> node_ptr;
    std::vector<IoInfo> input_conn_map;
    NodeDescription desc;
};

///@brief 连接信息
///
struct Wire
{
    uint64_t id{};
    IoInfo from;
    IoInfo to;
};

///@brief 管理器
///
class FlowCV_Manager
{
  private:
    uint64_t id_counter_;
    uint64_t wire_id_counter_;
    std::vector<NodeInfo> nodes_;
    std::vector<Wire> wiring_;
    std::shared_ptr<DSPatch::Circuit> circuit_;

  public:
    FlowCV_Manager();
    ~FlowCV_Manager();

    std::shared_ptr<PluginManager> plugin_manager_;
    std::shared_ptr<InternalNodeManager> internal_node_manager_;

    ///@brief 创建一个节点管理器的实例
    ///
    ///@param name
    ///@return uint64_t
    uint64_t CreateNewNodeInstance(const char *name);

    ///@brief
    ///
    ///@param num_buffers
    void SetBufferCount(uint32_t num_buffers);

    ///@brief Get the Buffer Count object
    ///
    ///@return int
    int GetBufferCount();

    ///@brief Get the Node Count object
    ///
    ///@return uint64_t
    uint64_t GetNodeCount();

    ///@brief Get the Node Info By Index object
    ///
    ///@param index
    ///@param nInfo
    ///@return true
    ///@return false
    bool GetNodeInfoByIndex(uint64_t index, NodeInfo &nInfo);

    ///@brief Get the Node Info By Id object
    ///
    ///@param id
    ///@param nInfo
    ///@return true
    ///@return false
    bool GetNodeInfoById(uint64_t id, NodeInfo &nInfo);
    int GetNodeIndexFromId(uint64_t id);
    uint64_t GetNodeIdFromIndex(uint64_t index);
    nlohmann::json GetState();
    void NewState();
    bool SetState(nlohmann::json &state);
    bool LoadState(const char *filepath);
    bool SaveState(const char *filepath);
    bool NodeHasUI(uint64_t index, GuiInterfaceType interface);
    void SetShowUI(uint64_t index, bool show);
    bool *GetShowUiPtr(uint64_t index);
    void ProcessNodeUI(uint64_t index, void *context, GuiInterfaceType interface);
    bool ConnectNodes(uint64_t from_id, uint32_t from_out_idx, uint64_t to_id, uint32_t to_in_idx);
    bool DisconnectNodes(uint64_t from_id, uint32_t from_out_idx, uint64_t to_id,
                         uint32_t to_in_idx);
    uint64_t GetWireCount();
    Wire GetWireInfoFromIndex(uint64_t index);
    uint64_t GetWireIdFromIndex(uint64_t index);
    void RemoveWireById(uint64_t id);
    void RemoveWireByIndex(uint64_t index);
    std::vector<Wire> GetNodeConnectionsFromId(uint64_t id);
    std::vector<Wire> GetNodeConnectionsFromIndex(uint64_t index);

    ///@brief
    ///
    ///@param ni
    void CheckInstCountValue(NodeInfo &ni);

    ///@brief
    ///
    ///@param node_id
    ///@param in_index
    ///@return true
    ///@return false
    bool DisconnectNodeInput(uint64_t node_id, uint32_t in_index);

    ///@brief
    ///
    ///@param node_id
    ///@return true
    ///@return false
    bool RemoveNodeInstance(uint64_t node_id);

    ///@brief
    ///
    ///@param mode
    void Tick(DSPatch::Component::TickMode mode = DSPatch::Component::TickMode::Parallel);

    ///@brief
    ///
    ///@param mode
    void StartAutoTick(DSPatch::Component::TickMode mode = DSPatch::Component::TickMode::Parallel);

    ///@brief
    ///
    void StopAutoTick();

  protected:
    ///@brief 添加新的节点实例
    ///
    ///@param name
    ///@param ext
    ///@param id
    ///@return uint64_t
    uint64_t AddNewNodeInstance(const char *name, bool ext = false, uint64_t id = 0);

    ///@brief 获取下一个id
    ///
    ///@return uint64_t
    uint64_t GetNextId();
};
}  // End Namespace FlowCV
