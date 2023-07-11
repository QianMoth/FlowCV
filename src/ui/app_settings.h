//
// Common App Setting Header
//

#ifndef FLOWCV_APP_SETTINGS_H_
#define FLOWCV_APP_SETTINGS_H_
#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

struct AppSettings
{
    std::string configPath;
    std::vector<std::string> extPluginDir;
    int recentListSize;
    std::deque<std::string> recentFiles;
    bool showFPS;
    bool useVSync;
    int flowBufferCount;
};

void ApplicationLoadSettings(AppSettings &settings);
void ApplicationSaveSettings(const AppSettings &settings);

#endif  // FLOWCV_APP_SETTINGS_H_
