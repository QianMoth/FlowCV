message(STATUS "Adding ImGUI Node Editor CMake Config")

set(IMGUI_NODE_EDITOR_DIR ${CMAKE_SOURCE_DIR}/3rdparty/node-editor)
include_directories(${IMGUI_NODE_EDITOR_DIR})
include_directories(${IMGUI_NODE_EDITOR_DIR}/external/stb_image)
include_directories(${IMGUI_NODE_EDITOR_DIR}/external/ScopeGuard)
add_subdirectory(${IMGUI_NODE_EDITOR_DIR}/external/ScopeGuard)
add_subdirectory(${IMGUI_NODE_EDITOR_DIR}/external/stb_image)

file(GLOB IMGUI_NODE_EDITOR_SRC ${CMAKE_SOURCE_DIR}/3rdparty/node-editor/*.cpp)
