file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE INCS *.hpp *.h)

if(WIN32)
    set(APP_ICON_RESOURCE_WINDOWS ${CMAKE_CURRENT_SOURCE_DIR}/resources/appicon.rc)
elseif(UNIX AND NOT APPLE)
    add_link_options(-fno-pie -no-pie -Wl,--disable-new-dtags)
    set(STB_IMAGE_LIB stb_image)
    FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Node_Editor_Resource)
    FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/AppIcon.png DESTINATION ${CMAKE_BINARY_DIR}/Node_Editor_Resource/)
endif()

target_sources(${PROJECT_NAME} PRIVATE ${INCS} ${SRCS} ${APP_ICON_RESOURCE_WINDOWS})
