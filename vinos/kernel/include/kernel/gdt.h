#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#ifdef __cplusplus
namespace kernel { namespace gdt {
#endif //__cplusplus

struct seg_desc {
    uint32_t base;
    uint32_t limit; //only 20 bits normally
    uint8_t access_byte;
    uint8_t flags;
};

#ifdef __cplusplus
#define SEGD seg_desc
#else
#define SEGD struct seg_desc
#endif

void encodeGDT(uint16_t* target, SEGD source);

#ifdef __cplusplus
}}
#endif //__cplusplus

#endif //GDT_H
