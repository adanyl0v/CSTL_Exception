#include "../include/Exception.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

static CSTL_Exception cstl_last_exception;

CSTL_Exception CSTL_GetException(void) {
    return cstl_last_exception;
}

int CSTL_SetException(const char *file, int line, int code, const char *description) {
    if (description == NULL || file == NULL)
        return CSTL_INVALID_ARGS;

    cstl_last_exception.code = code;
    cstl_last_exception.line = line;

    if (strcpy(cstl_last_exception.desc, description) != cstl_last_exception.desc)
        return CSTL_FAILED_STRCPY;

    if (strcpy(cstl_last_exception.file, file) != cstl_last_exception.file)
        return CSTL_FAILED_STRCPY;

    return 0;
}

int CSTL_ThrowExceptionIn(const char *file, int line, int code, const char *descFmt, ...) {
    va_list(args);
    va_start(args, descFmt);

    char description[CSTL_EXCEPTION_STRMAX] = "";
    vsnprintf(description, CSTL_EXCEPTION_STRMAX, descFmt, args);
    int ecode = CSTL_SetException(file, line, code, descFmt);
    if (ecode != 0)
        return ecode;

    fprintf(stderr, "Exception (%s:%d) with code %d: %s\n", file, line, code, description);
    
    va_end(args);
    exit(code);
    return code;
}

int CSTL_ThrowWarningIn(const char *file, int line, int code, const char *descFmt, ...) {
    va_list(args);
    va_start(args, descFmt);

    char description[CSTL_EXCEPTION_STRMAX] = "";
    vsnprintf(description, CSTL_EXCEPTION_STRMAX, descFmt, args);
    fprintf(stderr, "Warning (%s:%d) with code %d: %s\n", file, line, code, description);
    
    va_end(args);
    return code;
}

