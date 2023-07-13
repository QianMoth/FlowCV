cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 1)
set(PROJECT_VERSION_STATUS "")
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})
set(PROJECT_DESCRIPTION "An Open Source Data Flow Framework and Node Editor UI For Computer Vision")
set(PROJECT_HOMEPAGE_URL "http://www.flowcv.org")

project(
    FlowCVEngine
    VERSION ${PROJECT_VERSION}
    DESCRIPTION ${PROJECT_DESCRIPTION}
    HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL}
)

message(STATUS "[${PROJECT_NAME}] Project ${PROJECT_NAME} v${PROJECT_VERSION}")

# Options
option(USE_LOCAL_OPENCV_PACKAGE "Use locally OpenCV Package" ON)
option(BUILD_EXAMPLES "Build Examples" OFF)
option(BUILD_PLUGINS "Build Plugins" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "[${PROJECT_NAME}] Project is top? ${PROJECT_IS_TOP_LEVEL}")

if(PROJECT_IS_TOP_LEVEL)
    # 设置输出路径
    include(GNUInstallDirs)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}) # 静态库的文件夹位置
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}) # 动态库的文件夹位置
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}) # 可执行软件的文件夹位置
endif()

# 后缀
if(BUILD_DEBUG_POSTFIX_D)
    # 这个就是定义各个版本对应的后缀，例如d，debug版本后缀，当然你想定义为其他，自己修改这块就可以了。
    set(CMAKE_DEBUG_POSTFIX "d")
    set(CMAKE_RELEASE_POSTFIX "")
    set(CMAKE_RELWITHDEBINFO_POSTFIX "rd")
    set(CMAKE_MINSIZEREL_POSTFIX "s")
endif()

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

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/config.h")

add_library(${PROJECT_NAME})
add_library(FlowCV::FlowCVEngine ALIAS FlowCVEngine)

add_subdirectory(src)

# file(GLOB SRCS *.cpp)
# file(GLOB INCS *.hpp *.h)
target_sources(
    ${PROJECT_NAME}
    PRIVATE ${DSPatch_SRC}
    PRIVATE ${IMGUI_SRC}
    PRIVATE ${IMGUI_WRAPPER_SRC}
    PRIVATE ${IMGUI_NODE_EDITOR_SRC}
    PRIVATE ${IMGUI_OPENCV_SRC}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC $<INSTALL_INTERFACE:include>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/FlowCV>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/FlowCV/internal>
)

target_compile_definitions(
    ${PROJECT_NAME}
    PUBLIC
    FLOW_EDITOR_SHARED
    PRIVATE
    FLOW_EDITOR_EXPORTS
)

if(WIN32)
    target_link_libraries(
        ${PROJECT_NAME}
        ${IMGUI_LIBS}
        ${OpenCV_LIBS}
    )
else()
    target_link_libraries(
        ${PROJECT_NAME}
        ${IMGUI_LIBS}
        ${OpenCV_LIBS}
        ${STB_IMAGE_LIB}
        pthread
    )
endif()

if(WIN32)
    set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
elseif(UNIX AND NOT APPLE)
    set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        INSTALL_RPATH "${ORIGIN};./;./Plugins/OpenVino;./Plugins/RealSense;./Plugins/NDI;./Plugins/OakCamera"
        BUILD_WITH_INSTALL_RPATH ON
    )
elseif(APPLE)
    set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        INSTALL_NAME_DIR "${ORIGIN};./;./Plugins/OpenVino;./Plugins/RealSense;./Plugins/NDI;./Plugins/OakCamera"
        BUILD_WITH_INSTALL_NAME_DIR ON
    )
endif()

if(BUILD_PLUGINS)
    add_subdirectory(plugins)
endif()

add_subdirectory(examples/test)

# interface
add_subdirectory(examples/cli)
add_subdirectory(examples/ui)
