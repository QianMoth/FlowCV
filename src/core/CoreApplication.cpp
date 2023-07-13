#include "CoreApplication.hpp"

#include <filesystem>
#include <string>

#ifdef __linux__
#include <libgen.h>
#include <unistd.h>

#include <climits>
#endif
#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

namespace FlowCV
{

std::string CoreApplication::applicationName()
{
    return "FlowCV";
}

std::string CoreApplication::applicationFilePath()
{
    std::string filePath = applicationDirPath();
    filePath += std::filesystem::path::preferred_separator;
    filePath += "Flow";

    return filePath;
}

std::string CoreApplication::applicationDirPath()
{
#ifdef __linux__
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    const char *path;
    if (count != -1) {
        path = dirname(result);
    }
    return path;
#endif
#ifdef _WINDOWS
    appDir = std::filesystem::current_path().string();
    size_t requiredSize;
    getenv_s(&requiredSize, nullptr, 0, "APPDATA");
    if (requiredSize != 0) {
        char *libVar = new char[requiredSize];
        getenv_s(&requiredSize, libVar, requiredSize, "APPDATA");
        cfgDir = libVar;
        cfgDir += std::filesystem::path::preferred_separator;
        cfgDir += "FlowCV";
        if (!std::filesystem::exists(cfgDir)) {
            std::filesystem::create_directories(cfgDir);
        }
        delete[] libVar;
    }
    else {
        return appDir;
    }
#endif
#if __APPLE__
    char path[1024];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        std::filesystem::path p = path;
        return p.parent_path();
    }

    return std::filesystem::current_path().string();
#endif
}

}  // namespace FlowCV