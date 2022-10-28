# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

/*
Declare multiboot header that marks program as kernel. These are all magic values that are documented in multiboot standard. Bootloader will search for this signature in first 8 kiB of kernel file, aligned at 32-bit boundary. Signature is in its own section so the header can be forced to be within the first 8 KiB of the kernel file.
*/

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	/*
	this is a good place to init crucial processor state before the high-level
	is entered. It's best to minimize the early environment where crucial
	features are offline. note that the processor is not fully initialized
	yet: features such as floating point instructions and instruction set
	extensions are not initialized yet. The GDT should be loaded here. Paging
	should be enabled here. C++ features such as global constructors and
	exceptions will require runtime support to work as well.
	*/

	# Set up paging
	mov %eax, $page_directory
	mov %cr3, %eax

	mov %eax, %cr0
	or %eax, 0x80000001
	mov %cr0, %eax

	# enable PSE
	mov %eax, %cr4
	or %eax, 0x00000010
	mov %cr4, %eax

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
