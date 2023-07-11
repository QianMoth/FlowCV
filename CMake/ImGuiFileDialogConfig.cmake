message(STATUS "Adding ImGUI File Dialog CMake Config")

set(IMGUI_FILE_DIALOG_DIR ${CMAKE_SOURCE_DIR}/3rdparty/FileBrowser)
include_directories(${IMGUI_FILE_DIALOG_DIR})

if(WIN32)
    include_directories(${IMGUI_FILE_DIALOG_DIR}/Dirent)
endif()

list(APPEND IMGUI_WRAPPER_SRC "${IMGUI_FILE_DIALOG_DIR}/ImGuiFileBrowser.cpp")
