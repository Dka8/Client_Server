#ifndef CONFIG_H
#define CONFIG_H

#if defined (_WIN32)

    #define SYSTEM_WINDOWS
    #define _WIN32_WINNT 0x501

#elif defined(__unix__)

    #if defined (__ANDROID__)

    #elif defined (__linux__)
        #define SYSTEM_LINUX

    #elif defined (__FreeBSD__) || defined(__FreeBSD_kernel__)
        #define SYSTEM_FREEBSD

    #endif

#else

    #error This operating system is not supported

#endif

#if defined(SYSTEM_WINDOW)

    #define API_EXPORT __declspec(dllexport)
    #define API_IMPORT __declspec(dllimport)

#else // Linux, FreeBSD, Mac OS X

    #if __GNUC__ >= 4
        #define API_EXPORT __attribute__ ((__visibility__ ("default")))
        #define API_IMPORT __attribute__ ((__visibility__ ("default")))

    #else
        #define API_EXPORT
        #define API_IMPORT

    #endif

#endif

#endif
