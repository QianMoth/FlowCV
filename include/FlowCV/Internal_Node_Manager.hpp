//
// FlowCV Internal Component Manager
//

#pragma once

#include <DSPatch.h>

#include <iostream>

#include "Types.hpp"

namespace FlowCV {

class InternalNodeManager
{
  public:
    InternalNodeManager();
    ~InternalNodeManager() = default;
    uint32_t NodeCount();
    bool GetNodeDescription(uint32_t index, NodeDescription &nodeDesc);
    bool GetNodeDescription(const char *name, NodeDescription &nodeDesc);
    std::shared_ptr<DSPatch::Component> CreateNodeInstance(const char *name);
    bool HasNode(const char *name);

  protected:
  private:
    std::vector<NodeDescription> node_list_;
};
}  // End Namespace FlowCV
