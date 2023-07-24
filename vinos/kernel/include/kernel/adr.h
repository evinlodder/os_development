#ifndef ADR_H
#define ADR_H

#ifdef __cplusplus
namespace kernel { namespace address {
#endif //__cplusplus

void *get_physaddr(void *virtualaddr);
void map_page(void *physaddr, void *virtualaddr, unsigned int flags);

#ifdef __cplusplus
}}
#endif //__cplusplus

#endif //ADR_H
