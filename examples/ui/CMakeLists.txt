
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 2)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 0)
set(PROJECT_VERSION_STATUS "")
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})
set(PROJECT_DESCRIPTION "An Open Source Data Flow Framework and Node Editor UI For Computer Vision")
set(PROJECT_HOMEPAGE_URL "http://www.flowcv.org")

project(
    flowcv
    VERSION ${PROJECT_VERSION}
    DESCRIPTION ${PROJECT_DESCRIPTION}
    HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL}
)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/config.h")

if(WIN32)
    set(APP_ICON_RESOURCE_WINDOWS ${CMAKE_CURRENT_SOURCE_DIR}/resources/appicon.rc)
elseif(UNIX AND NOT APPLE)
    add_link_options(-fno-pie -no-pie -Wl,--disable-new-dtags)
    set(STB_IMAGE_LIB stb_image)
    FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Node_Editor_Resource)
    FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/AppIcon.png DESTINATION ${CMAKE_BINARY_DIR}/Node_Editor_Resource/)
endif()

file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE INCS *.hpp *.h)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${INCS} ${SRCS} ${APP_ICON_RESOURCE_WINDOWS})

target_link_libraries(${PROJECT_NAME} FlowCVEngine)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC $<INSTALL_INTERFACE:include>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
