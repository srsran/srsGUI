#ifndef CONFIG_H
#define CONFIG_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define LIBSDRGUI_IMPORT __declspec(dllimport)
  #define LIBSDRGUI_EXPORT __declspec(dllexport)
  #define LIBSDRGUI_LOCAL
#else
  #if __GNUC__ >= 4
    #define LIBSDRGUI_IMPORT __attribute__ ((visibility ("default")))
    #define LIBSDRGUI_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define LIBSDRGUI_IMPORT
    #define LIBSDRGUI_EXPORT
    #define LIBSDRGUI_LOCAL
  #endif
#endif

// Define LIBSDRGUI_API
// LIBSDRGUI_API is used for the public API symbols.
#ifdef LIBSDRGUI_DLL_EXPORTS // defined if we are building the LIBSDRGUI DLL (instead of using it)
  #define LIBSDRGUI_API LIBSDRGUI_EXPORT
#else
  #define LIBSDRGUI_API LIBSDRGUI_IMPORT
#endif


// Common error codes
#define LIBSDRGUI_SUCCESS                 0
#define LIBSDRGUI_ERROR                  -1
#define LIBSDRGUI_ERROR_INVALID_INPUTS   -2

#endif // CONFIG_H
