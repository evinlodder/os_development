#include <kernel/pic.h>
#include <kernel/hio.h>
//remapping is necessary since the original mappings are first 8 and last 8 in IDT, instead of just first 16
EXTERN void kernel::pic::remap_pic(uint32_t pic1, uint32_t pic2) {
    using namespace kernel::hio;

    byte md{}, sd{};
    md = in_port_b(MASTERDATA); //save state of master data
    sd = in_port_b(SLAVEDATA);  //save state of slave data

    out_port_b(MASTER, EOI); //resets the chip

    out_port_b(MASTER, ICW1_INIT+ICW1_ICW4);      // ICW1 control word setup | just basic PIC stuff
	out_port_b(SLAVE, ICW1_INIT+ICW1_ICW4);       // see pic.h for more details about the values

	out_port_b(MASTERDATA, pic1);                 // ICW2 maps IRQs 0-7 to whatever kernel passes
	out_port_b(SLAVEDATA, pic2);                  // and same here except with IRQs 8-15

	out_port_b(MASTERDATA, 0x04);                 // ICW3
	out_port_b(SLAVEDATA, 0x02);

	out_port_b(MASTERDATA, ICW4_8086);            // ICW4 control word setup
	out_port_b(SLAVEDATA, ICW4_8086);

	out_port_b(MASTERDATA, md);                    // restore both MASTER DATA
	out_port_b(SLAVEDATA, sd);                     // restore SLAVE DATA
}

EXTERN void kernel::pic::mask_irq(byte irq) {
    using namespace kernel::hio;
    if(irq==ALL)
	{
		out_port_b(MASTERDATA,0xFF);
		out_port_b(SLAVEDATA,0xFF);
	}
	else
	{
		irq = irq | (1<<irq);
		if(irq < 8)
			out_port_b(MASTERDATA, irq&0xFF);
		else
			out_port_b(SLAVEDATA, irq>>8);
	}
}

EXTERN void kernel::pic::unmask_irq(byte irq) {
    using namespace kernel::hio;
    if(irq==ALL)
	{
		out_port_b(MASTERDATA,0x00);
		out_port_b(SLAVEDATA,0x00);
	}
	else
	{
		irq = irq & (1<<irq);
		if(irq < 8)
			out_port_b(MASTERDATA, irq&0xFF);
		else
			out_port_b(SLAVEDATA, irq>>8);
	}
}
