# beginning of GDT
gdt_begin:

null_descriptor:
	.quad 0
code_descriptor:
	.word 0xffff # first 16 bits of limit
	.word 0 # first 24 bits of base
	.byte 0 # first 24 bits of base
	.byte 0b10011010
	# access byte:
	# 1 : present
	# 00: privelage (kernel)
	# 1 : type (code/data)
	# 1 : executable (code segment)
	# 0 : conforming bit (can only be executed by kernel)
	# 1 : read/write (write allowed)
	# 0 : accessed (always leave 0)
	.byte 0b11001111
	# flags / rest of limit
	# 1 : granularity (4 KiB blocks / pages)
	# 1 : size flag (32-bit protected mode segment)
	# 0 : long-mode (code segment)
	# 0 : reserved bit
	# 1111 : rest of limit
	.byte 0 #rest of base
data_descriptor:
	.word 0xffff
	.word 0
	.byte 0
	.byte 0b10010010
	# changed bit: executable bit (data isn't executable)
	.byte 0b11001111
	.byte 0

gdt_end:
# end of GDT

# GDT descriptor
gdt_descriptor:
	.word (gdt_end - gdt_begin - 1)
	.long (gdt_begin)

# constants for descriptor offsets
.set code_segment, (code_descriptor - gdt_begin)
.set data_segment, (data_descriptor - gdt_begin)

