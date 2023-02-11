#ifndef SYSDEFS_H
#define SYSDEFS_H

//some commonplace defines
#include <stdint.h>
#ifdef __cplusplus
#define VOID
#define EXTERN extern "C"
#else // if compiling with C
#define VOID void
typedef enum {false = 0, true = 1} bool;
#define EXTERN

#endif //__cplusplus

#define byte uint8_t
#define word uint16_t
#define quad long long
#define PRIVATE static
//


#endif //SYSDEFS_H
