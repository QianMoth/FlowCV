cmake_minimum_required(VERSION 3.15)

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 1)
set(PROJECT_VERSION_STATUS "")
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})
set(PROJECT_DESCRIPTION "An Open Source Data Flow Framework and Node Editor UI For Computer Vision")
set(PROJECT_HOMEPAGE_URL "http://www.flowcv.org")

project(
    FlowCV
    VERSION ${PROJECT_VERSION}
    DESCRIPTION ${PROJECT_DESCRIPTION}
    HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL}
)

message(STATUS "[${PROJECT_NAME}] Project ${PROJECT_NAME} v${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(USE_LOCAL_OPENCV_PACKAGE "Use locally OpenCV Package" ON)
option(BUILD_EXAMPLES "Build Examples" OFF)
option(BUILD_PLUGINS "Build Plugins" ON)
option(BUILD_EDITOR "Build Editor" ON)
option(BUILD_ENGINE "Build Engine" ON)

# Include all modules by default, modify based on your project needs
include(${CMAKE_SOURCE_DIR}/cmake/ImGuiOpenCvConfig.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/ImGuiGlfwConfig.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/ImGuiWrapperConfig.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/ImGui3DOpenGLConfig.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/ImGuiPlotConfig.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/ImGuiNodeEditorConfig.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/ImGuiFileDialogConfig.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/DSPatchConfig.cmake)

# header
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/json/include) # json
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/cmdline/include) # cli
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/spdlog/include) # log

include_directories(${CMAKE_SOURCE_DIR}/include) # sdk header

add_subdirectory(src)

if(BUILD_PLUGINS)
    add_subdirectory(plugins)
endif()

if(BUILD_EXAMPLES)
    # Build Examples
    add_subdirectory(examples/FlowCV_Dataflow_Test)
endif()
