message(STATUS "Adding DSPatch CMake Config")

# DSPatch Library
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/dspatch/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/dspatch/src)
file(GLOB_RECURSE DSPatch_SRC ${CMAKE_SOURCE_DIR}/3rdparty/dspatch/src/*.cpp)
