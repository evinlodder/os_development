#include <kernel/paging.h>

extern "C" uint32_t boot_page_directory[1024];

void kernel::map_page(void* physaddr, void* virtaddr, ::uint8_t flags) {
    //make sure that addresses are page aligned
/*
    unsigned long pdindex = (unsigned long)virtaddr >> 22;
    unsigned long ptindex = (unsigned long)virtaddr >> 12 & 0x03FF;

    unsigned long* pd = (unsigned long*)0xFFFFF000;
    //check whether pd entry is present
    //when isn't create new empty pt and adjust pde accordingly
    //
    unsigned long* pt = ((unsigned long*)0xFFC00000) + (0x400 * pdindex);
    //check whether pt entry is present
    //when is, mapping present

    pt[ptindex] = ((unsigned long)physaddr) | (flags & 0xFFF) | 0x01; //present
    //now flush entry in tlb or you may not notice change*/
}
