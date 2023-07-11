cmake_minimum_required(VERSION 3.15)

set(FLOWCV_VERSION_MAJOR 1)
set(FLOWCV_VERSION_MINOR 1)
set(FLOWCV_VERSION_PATCH 0)
set(FLOWCV_VERSION_TWEAK 1)
set(FLOWCV_VERSION_STATUS "")
set(FLOWCV_VERSION ${FLOWCV_VERSION_MAJOR}.${FLOWCV_VERSION_MINOR}.${FLOWCV_VERSION_PATCH}.${FLOWCV_VERSION_TWEAK})

project(
    FlowCV
    VERSION ${FLOWCV_VERSION}
)

message(STATUS "[${PROJECT_NAME}] Project ${PROJECT_NAME} v${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 17)

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
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/json/include) # JSON
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/tclap/include) # cmdline

include_directories(${CMAKE_SOURCE_DIR}/include) # sdk header

add_subdirectory(src)

if(BUILD_PLUGINS)
    add_subdirectory(plugins)
endif()

if(BUILD_EXAMPLES)
    # Build Examples
    add_subdirectory(examples/FlowCV_Dataflow_Test)
endif()
