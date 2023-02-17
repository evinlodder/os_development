#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>

#ifdef __cplusplus
namespace kernel {
#endif

    void map_page(void*, void*, uint8_t);

#ifdef __cplusplus
}
#endif

#endif
