#pragma once

#if defined(__MINGW32__) || defined(__MINGW64__)
#define FLOW_EDITOR_COMPILER "MinGW"
#define FLOW_EDITOR_COMPILER_MINGW
#elif defined(__clang__)
#define FLOW_EDITOR_COMPILER "Clang"
#define FLOW_EDITOR_COMPILER_CLANG
#elif defined(_MSC_VER)
#define FLOW_EDITOR_COMPILER "Microsoft Visual C++"
#define FLOW_EDITOR_COMPILER_MICROSOFT
#elif defined(__GNUC__)
#define FLOW_EDITOR_COMPILER "GNU"
#define FLOW_EDITOR_COMPILER_GNU
#define FLOW_EDITOR_COMPILER_GNU_VERSION_MAJOR __GNUC__
#define FLOW_EDITOR_COMPILER_GNU_VERSION_MINOR __GNUC_MINOR__
#define FLOW_EDITOR_COMPILER_GNU_VERSION_PATCH __GNUC_PATCHLEVEL__
#elif defined(__BORLANDC__)
#define FLOW_EDITOR_COMPILER "Borland C++ Builder"
#define FLOW_EDITOR_COMPILER_BORLAND
#elif defined(__CODEGEARC__)
#define FLOW_EDITOR_COMPILER "CodeGear C++ Builder"
#define FLOW_EDITOR_COMPILER_CODEGEAR
#elif defined(__INTEL_COMPILER) || defined(__ICL)
#define FLOW_EDITOR_COMPILER "Intel C++"
#define FLOW_EDITOR_COMPILER_INTEL
#elif defined(__xlC__) || defined(__IBMCPP__)
#define FLOW_EDITOR_COMPILER "IBM XL C++"
#define FLOW_EDITOR_COMPILER_IBM
#elif defined(__HP_aCC)
#define FLOW_EDITOR_COMPILER "HP aC++"
#define FLOW_EDITOR_COMPILER_HP
#elif defined(__WATCOMC__)
#define FLOW_EDITOR_COMPILER "Watcom C++"
#define FLOW_EDITOR_COMPILER_WATCOM
#endif

#ifndef FLOW_EDITOR_COMPILER
#error "Current compiler is not supported."
#endif
