#pragma once

#include <string>

namespace FlowCV {

class CoreApplication
{
  public:
    ///@brief 可执行文件名
    ///
    ///@return std::string 文件名称
    static std::string applicationName();

    ///@brief 可执行文件绝对路径
    ///
    ///@return std::string 文件路径
    static std::string applicationFilePath();

    ///@brief 可执行文件所在目录
    ///
    ///@return std::string 文件所在文件夹路径
    static std::string applicationDirPath();
};

}  // namespace FlowCV