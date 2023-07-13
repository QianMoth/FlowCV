#pragma once

#include "Compiler.hpp"
#include "OperatingSystem.hpp"

#ifdef FLOW_EDITOR_PLATFORM_WINDOWS
#define FLOW_EDITOR_EXPORT __declspec(dllexport)
#define FLOW_EDITOR_IMPORT __declspec(dllimport)
#define FLOW_EDITOR_LOCAL
#elif FLOW_EDITOR_COMPILER_GNU_VERSION_MAJOR >= 4 || defined(FLOW_EDITOR_COMPILER_CLANG)
#define FLOW_EDITOR_EXPORT __attribute__((visibility("default")))
#define FLOW_EDITOR_IMPORT __attribute__((visibility("default")))
#define FLOW_EDITOR_LOCAL __attribute__((visibility("hidden")))
#else
#define FLOW_EDITOR_EXPORT
#define FLOW_EDITOR_IMPORT
#define FLOW_EDITOR_LOCAL
#endif

#ifdef __cplusplus
#define FLOW_EDITOR_DEMANGLED extern "C"
#else
#define FLOW_EDITOR_DEMANGLED
#endif

#if defined(FLOW_EDITOR_SHARED) && !defined(FLOW_EDITOR_STATIC)
#ifdef FLOW_EDITOR_EXPORTS
#define FLOW_EDITOR_PUBLIC FLOW_EDITOR_EXPORT
#else
#define FLOW_EDITOR_PUBLIC FLOW_EDITOR_IMPORT
#endif
#define FLOW_EDITOR_PRIVATE FLOW_EDITOR_LOCAL
#elif !defined(FLOW_EDITOR_SHARED) && defined(FLOW_EDITOR_STATIC)
#define FLOW_EDITOR_PUBLIC
#define FLOW_EDITOR_PRIVATE
#elif defined(FLOW_EDITOR_SHARED) && defined(FLOW_EDITOR_STATIC)
#ifdef FLOW_EDITOR_EXPORTS
#error "Cannot build as shared and static simultaneously."
#else
#error "Cannot link against shared and static simultaneously."
#endif
#else
#ifdef FLOW_EDITOR_EXPORTS
#error "Choose whether to build as shared or static."
#else
#error "Choose whether to link against shared or static."
#endif
#endif
