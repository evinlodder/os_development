.global l_idt
.extern idt_des
l_idt:
 lidt (idt_des)
 ret
