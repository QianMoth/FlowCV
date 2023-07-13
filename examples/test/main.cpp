//
// Headless (No GUI) Processing Engine
//

#include <spdlog/spdlog.h>

#include <FlowCV/CoreApplication.hpp>
#include <FlowCV/FlowCV_Manager.hpp>
#include <FlowCV/Properties.hpp>
#include <FlowCV/Settings.hpp>
#include <chrono>
#include <cmdline/cmdline>
#include <csignal>
#include <filesystem>
#include <iostream>
#include <thread>

#ifdef __linux__
#include <libgen.h>
#include <unistd.h>

#include <climits>
#endif
#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

#include "config.h"

unsigned int g_bTerminate = 0;

void SignalHandler(int iSignal)
{
    if ((iSignal == SIGINT) || (iSignal == SIGTERM)) {
        g_bTerminate = 1;
    }
}

int Init_Signal()
{
    if (signal(SIGINT, SignalHandler) == SIG_ERR) {
        return -1;
    }

    if (signal(SIGTERM, SignalHandler) == SIG_ERR) {
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    AppSettings appSettings;

    std::string appDir = FlowCV::CoreApplication::applicationDirPath();
    const std::string &cfgDir = appDir;

    // 命令行解析器
    cmdline::parser cmdParser;
    cmdParser.set_program_name(std::string(PROJECT_NAME) + " " + PROJECT_VER);
    // 执行flow文件
    cmdParser.add<std::string>("flow", 'f', "Flow File", true);
    cmdParser.add<std::string>("cfg", 'c', "Default Config File Override", false);

    cmdParser.parse_check(argc, argv);

    spdlog::info("FlowCV Processing Engine - v{}", PROJECT_VER);

    // ===========================================================================

    FlowCV::FlowCV_Manager flowMan;

    // 配置文件加载
    std::string configFile;
    if (cmdParser.exist("cfg")) {
        auto cfg_file_arg = cmdParser.get<std::string>("cfg");
        if (cfg_file_arg.empty()) {
            configFile = cfgDir;
            configFile += std::filesystem::path::preferred_separator;
            configFile += "flowcv_editor.cfg";
        } else {
            configFile = cfg_file_arg;
        }
    }
    appSettings.configPath = configFile;
    ApplicationLoadSettings(appSettings);

    // 获取主程序内部的插件
    std::string pluginDir = appDir;
    pluginDir += std::filesystem::path::preferred_separator;
    pluginDir += "Plugins";
    if (std::filesystem::exists(pluginDir)) {
        flowMan.plugin_manager_->LoadPlugins(pluginDir.c_str());
    }

    // 获取外部的插件
    if (!appSettings.extPluginDir.empty()) {
        for (const auto &path : appSettings.extPluginDir) {
            if (std::filesystem::exists(path)) {
                flowMan.plugin_manager_->LoadPlugins(path.c_str(), false);
            }
        }
    }
    spdlog::info("{} Plugin(s) Loaded", flowMan.plugin_manager_->PluginCount());

    // ===========================================================================

    // 加载外部的flow文件
    if (cmdParser.exist("flow")) {
        auto flow_file_arg = cmdParser.get<std::string>("flow");
        spdlog::info("Loading Flow File: {}", flow_file_arg);
        if (!flowMan.LoadState(flow_file_arg.c_str())) {
            std::cout << "Error Loading Flow File" << std::endl;
            return EXIT_FAILURE;
        }
    }

    spdlog::info("Flow State Loaded, {} Nodes Loaded and Configured", flowMan.GetNodeCount());

    // Init Signal Handling (Cntrl-C, Cntrl-X to clean exit)
    Init_Signal();

    spdlog::info("Flow Processing Started");

    // Start Multi-Threaded Flow Processing in Background
    flowMan.StartAutoTick();

    while (!g_bTerminate) {
        // 当Circuit Flow 在运行的时候， 你可以做一些其他的事情，在这里只添加了1s的延时。
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Stop Flow Before Going Out of Scope and Cleanup
    flowMan.StopAutoTick();

    spdlog::info("Flow Processing Stopped\nExiting");

    return EXIT_SUCCESS;
}
