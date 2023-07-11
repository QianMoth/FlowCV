message(STATUS "Adding ImGUI Wrapper CMake Config")

set(IMGUI_WRAPPER_DIR ${CMAKE_SOURCE_DIR}/3rdparty/imgui_wrapper)
include_directories(${IMGUI_WRAPPER_DIR})

list(APPEND IMGUI_WRAPPER_SRC "${IMGUI_WRAPPER_DIR}/imgui_wrapper.cpp")
list(APPEND IMGUI_WRAPPER_SRC "${IMGUI_WRAPPER_DIR}/imgui_instance_helper.cpp")
