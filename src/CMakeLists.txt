add_executable(${PROJECT_NAME})

add_subdirectory(core)
add_subdirectory(ui)
add_subdirectory(managers)
add_subdirectory(nodes)

file(GLOB SRCS *.cpp)
file(GLOB INCS *.hpp *.h)

target_sources(
    ${PROJECT_NAME}
    PRIVATE main.cpp
    PRIVATE ${DSPatch_SRC}
    PRIVATE ${IMGUI_SRC}
    PRIVATE ${IMGUI_WRAPPER_SRC}
    PRIVATE ${IMGUI_NODE_EDITOR_SRC}
    PRIVATE ${IMGUI_OPENCV_SRC}
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core>
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME}
        ${IMGUI_LIBS}
        ${OpenCV_LIBS}
    )
else()
    target_link_libraries(${PROJECT_NAME}
        ${IMGUI_LIBS}
        ${OpenCV_LIBS}
        ${STB_IMAGE_LIB}
        pthread
    )
endif()

if(WIN32)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
elseif(UNIX AND NOT APPLE)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        INSTALL_RPATH "${ORIGIN};./;./Plugins/OpenVino;./Plugins/RealSense;./Plugins/NDI;./Plugins/OakCamera"
        BUILD_WITH_INSTALL_RPATH ON
    )
elseif(APPLE)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        INSTALL_NAME_DIR "${ORIGIN};./;./Plugins/OpenVino;./Plugins/RealSense;./Plugins/NDI;./Plugins/OakCamera"
        BUILD_WITH_INSTALL_NAME_DIR ON
    )
endif()
