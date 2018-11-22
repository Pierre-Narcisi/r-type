/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ctor.hpp
*/

#include <stdlib.h>
#if defined (_MSC_VER)
#if (_MSC_VER >= 1500)
/* Visual Studio 2008 and later have __pragma */
#define HAS_CONSTRUCTORS
#define CONSTRUCTOR(_func) \
    static void _func(void); \
    static int _func ## _wrapper(void) { _func(); return 0; } \
    __pragma(section(".CRT$XCU",read)) \
    __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _wrapper;
#define DESTRUCTOR(_func) \
    static void _func(void); \
    static int _func ## _constructor(void) { atexit (_func); return 0; } \
    __pragma(section(".CRT$XCU",read)) \
    __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;
#elif (_MSC_VER >= 1400)
/* Visual Studio 2005 */
#define HAS_CONSTRUCTORS
#pragma section(".CRT$XCU",read)
#define CONSTRUCTOR(_func) \
    static void _func(void); \
    static int _func ## _wrapper(void) { _func(); return 0; } \
    __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _wrapper;
#define DESTRUCTOR(_func) \
    static void _func(void); \
    static int _func ## _constructor(void) { atexit (_func); return 0; } \
    __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;
#else
/* Visual Studio 2003 and early versions should use #pragma code_seg() to define pre/post-main functions. */
#error Pre/Post-main function not supported on your version of Visual Studio.
#endif
#elif (__GNUC__ > 2) || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)
#define HAS_CONSTRUCTORS
#define CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);
#else
/* not supported */
#endif