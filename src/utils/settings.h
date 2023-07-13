//
// Common App Setting Header
//

#pragma once

#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

struct AppSettings
{
    std::string configPath;  // 配置路径
    std::vector<std::string> extPluginDir;
    int recentListSize;
    std::deque<std::string> recentFiles;
    bool showFPS;
    bool useVSync;
    int logLevel;  // 日志等级
    int flowBufferCount;
};

void ApplicationLoadSettings(AppSettings &settings);
void ApplicationSaveSettings(const AppSettings &settings);
