#ifndef HIO_H
#define HIO_H
#include <kernel/system.h>

#ifdef __cplusplus
namespace kernel { namespace hio {
#endif //__cplusplus

EXTERN void out_port_b(uint32_t port, byte value);
EXTERN void out_port_w(uint32_t port, uint32_t value);
EXTERN byte in_port_b(uint32_t port);

#ifdef __cplusplus
}}
#endif //__cplusplus

#endif //HIO_H
