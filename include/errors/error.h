#ifndef ERROR_H
#define ERROR_H

#include <stdbool.h>

static inline bool IsNullPtr(void *ptr) { return !ptr; }
void HandleNullPtr(void *ptr, const char *errormsg, bool fatal, const char *file, int line);

static inline bool IsNonZeroReturn(int retval) { return retval != 0; }
void HandleNonZeroReturn(int retval, const char *errormsg, bool fatal, const char *file, int line);

#define HANDLE_NULL_PTR(ptr, msg) HandleNullPtr(ptr, msg, true, __FILE__, __LINE__)
#define HANDLE_NONZERO_RET(retval, msg) HandleNonZeroReturn(retval, msg, true, __FILE__, __LINE__)

#define WARN_NULL_PTR(ptr, msg) HandleNullPtr(ptr, msg, false, __FILE__, __LINE__)
#define WARN_NONZERO_RET(retval, msg) HandleNonZeroReturn(retval, msg, false, __FILE__, __LINE__)

#endif