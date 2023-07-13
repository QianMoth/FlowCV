#pragma once

#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

///@brief 全局配置
///
struct AppSettings
{
    std::string configPath;                 // 配置路径
    std::vector<std::string> extPluginDir;  // 插件路径
    int recentListSize;                     // 最近打开文件个数
    std::deque<std::string> recentFiles;    // 最近打开的文件
    bool showFPS;                           // 显示刷新率
    bool useVSync;
    int logLevel;  // 日志等级
    int flowBufferCount;
};

///@brief 加载配置类
///
///@param settings
void ApplicationLoadSettings(AppSettings &settings);

///@brief 保存配置类
///
///@param settings
void ApplicationSaveSettings(const AppSettings &settings);
