.include "arch/i386/setup.s"

.section .text

.include "arch/i386/interrupts.s"
.include "arch/i386/idt.s"

4:
	# At this point, paging is fully set up and enabled.
    # Unmap the identity mapping as it is now unnecessary.
	movl $0, boot_page_directory + 0
    movl $0, boot_page_directory + 4

	# Reload crc3 to force a TLB flush so the changes to take effect.
	movl %cr3, %ecx
	movl %ecx, %cr3


    # we want to preserve the value of eax
    mov %eax, %ecx

	# clear interrupts for gdt
	cli
	# set up GDT
	xor %ax, %ax
	mov %ax, %ds
	lgdt (gdt_descriptor)
	# set CR0 to 1
	mov %cr0, %eax
	or $1, %eax
	mov %eax, %cr0 # now in 32-bit protected mode
 	# long jump to protected mode
	ljmp $code_segment, $start_protected_mode

	#[bits 32]
	start_protected_mode:
 	# reload registers
	mov $data_segment, %ax
	mov %ax, %ds
	mov %ax, %ss
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs

    mov $stack_top, %esp

    # restore eax and push values onto stack for mem setup
    mov %ecx, %eax

    pushl $boot_page_table2
    pushl $boot_page_table1
    pushl $boot_page_directory
    pushl %eax
    pushl $0xC03FE000 #yes i know its hard coded
    pushl $boot_fixed_allocbuffer

#					      #
# GDT IS SET UP, WE ARE NOW IN PROTECTED MODE #
#					      #
	# Set up system, things like IDT
    	call system_setup

    	# get GRUBs memory map
    	call setup_mem

	# Enter the high-level kernel.
	call kernel_main

	# Infinite loop if the system has nothing more to do.
1:	hlt
	jmp 1b

