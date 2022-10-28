.section .init
	# gcc will put contents of crtend.o .init section here
	popl %ebp
	ret

.section .fini
	popl %ebp
	ret

