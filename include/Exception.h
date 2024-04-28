#pragma once
#ifndef CSTL_EXCEPTION_H
#define CSTL_EXCEPTION_H

#include "BeginCode.h"

#ifndef CSTL_EXCEPTION_STRMAX
#define CSTL_EXCEPTION_STRMAX 4096
#endif

#ifndef CSTL_EXCEPTION_LOCAL
#define CSTL_EXCEPTION_LOCAL (__FILE__), (__LINE__)
#endif

typedef enum CSTL_Error {
    CSTL_INVALID_ARGS = 2,
    CSTL_FAILED_ALLOC,
    CSTL_OUT_OF_RANGE,
    CSTL_FAILED_STRCPY,
    CSTL_NOT_FOUND
} CSTL_Error;

typedef struct CSTL_Exception
{
    int code;
    int line;
    char desc[CSTL_EXCEPTION_STRMAX];
    char file[CSTL_EXCEPTION_STRMAX];
} CSTL_Exception;

#ifdef __cplusplus
extern "C"
{
#endif

    extern DECLSPEC CSTL_Exception CSTLCALL CSTL_GetLastException(void);

    extern DECLSPEC int CSTLCALL CSTL_ThrowExceptionIn(const char *file, int line, int code, const char *descFmt, ...);
    extern DECLSPEC int CSTLCALL CSTL_ThrowWarningIn(const char *file, int line, int code, const char *descFmt, ...);

#ifndef CSTL_ThrowException
    #define CSTL_ThrowException(C, DFMT...) \
        CSTL_ThrowExceptionIn(CSTL_EXCEPTION_LOCAL, C, DFMT)
#endif /* CSTL_ThrowException */
    
#ifndef CSTL_ThrowWarning
    #define CSTL_ThrowWarning(C, DFMT...) \
        CSTL_ThrowWarningIn(CSTL_EXCEPTION_LOCAL, C, DFMT)
#endif /* CSTL_ThrowWarning */

#ifdef __cplusplus
};
#endif

#endif /* CSTL_EXCEPTION_H */
