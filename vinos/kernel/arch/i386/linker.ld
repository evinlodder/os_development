ENTRY (_start)

kernel_addr_offset = 0xC0000000;

SECTIONS
{
        . = 0x00100000;
	/* The kernel will live at 3GB + 1MB in the virtual address space, */
	/* which will be mapped to 1MB in the physical address space. */
	/* Note that we page-align the sections. */

	_kernel_start = .;
        .multiboot.data : {
            *(.multiboot.data)
        }

       .multiboot.text : {
           *(.multiboot.text)
       }

	. += kernel_addr_offset;
	/* Add a symbol that indicates the start address of the kernel. */
	_new_kernel_start = .;
	.text ALIGN (4K) : AT (ADDR (.text) - kernel_addr_offset)
	{
		*(.text)
	}
	.rodata ALIGN (4K) : AT (ADDR (.rodata) - kernel_addr_offset)
	{
		*(.rodata)
	}
	.data ALIGN (4K) : AT (ADDR (.data) - kernel_addr_offset)
	{
		*(.data)
	}
	.bss ALIGN (4K) : AT (ADDR (.bss) - kernel_addr_offset)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
	/* Add a symbol that indicates the end address of the kernel. */
	_kernel_end = .;
}
