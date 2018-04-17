#include "shared.h"
#include "falcsys.h"
/* SMS context */
t_sms sms;

/* Run the virtual console emulation for one frame */
void sms_frame(int skip_render)
{
    /* Take care of hard resets */
    if(input.system & INPUT_HARD_RESET)
    {
        system_reset();
    }

    /* Debounce pause key */
    if(input.system & INPUT_PAUSE)
    {
        if(!sms.paused)
        {
            sms.paused = 1;

            z80_set_nmi_line(ASSERT_LINE);
            z80_set_nmi_line(CLEAR_LINE);
        }
    }
    else
    {
         sms.paused = 0;
    }

    for(vdp.line = 0; vdp.line < 262; vdp.line += 1)
    {
        /* Handle VDP line events */
        vdp_run();

        /* Draw the current frame */
        /*if(!skip_render)*/ render_line(vdp.line);

        /* Run the Z80 for a line */
        z80_execute(227);
    }
}


void sms_init(void)
{
    cpu_reset();
    sms_reset();
}


void sms_reset(void)
{
    /* Clear SMS context */
    //memset(sms.dummy, 0, 0x2000);
    //memset(sms.ram, 0, 0x2000);
    //memset(sms.sram, 0, 0x8000);
    VFastClear32(sms.dummy, 0x2000, 0);
    VFastClear32(sms.ram, 0x2000, 0);
    VFastClear32(sms.sram, 0x8000, 0);
    
    sms.paused = sms.save = sms.port_3F = sms.port_F2 = sms.irq = 0x00;
    sms.psg_mask = 0xFF;

    /* Load memory maps with default values */
    cpu_readmap[0] = cart.rom + 0x0000;
    cpu_readmap[1] = cart.rom + 0x2000;
    cpu_readmap[2] = cart.rom + 0x4000;
    cpu_readmap[3] = cart.rom + 0x6000;
    cpu_readmap[4] = cart.rom + 0x0000;
    cpu_readmap[5] = cart.rom + 0x2000;
    cpu_readmap[6] = sms.ram;            
    cpu_readmap[7] = sms.ram;

    cpu_writemap[0] = sms.dummy;       
  
    cpu_writemap[1] = sms.dummy;
    cpu_writemap[2] = sms.dummy;         
    cpu_writemap[3] = sms.dummy;
    cpu_writemap[4] = sms.dummy;         
    cpu_writemap[5] = sms.dummy;
    cpu_writemap[6] = sms.ram;           
    cpu_writemap[7] = sms.ram;

    sms.fcr[0] = 0x00;
    sms.fcr[1] = 0x00;
    sms.fcr[2] = 0x01;
    sms.fcr[3] = 0x00;
}


/* Reset Z80 emulator */
void cpu_reset(void)
{
    z80_reset(0);
    z80_set_irq_callback(sms_irq_callback);
}


/* Write to memory */
void cpu_writemem16(int address, int data)
{
    cpu_writemap[(address >> 13)][(address & 0x1FFF)] = data;
    if(address >= 0xFFFC) sms_mapper_w(address & 3, data);
}


/* Write to an I/O port */
void cpu_writeport(int port, int data)
{
    switch(port & 0xFF)
    {
        case 0x01: /* GG SIO */
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x05:
            break;

        case 0x06: /* GG STEREO */
            if(snd.log) {
            snd.callback(0x04);
            snd.callback(data);
            }
            sms.psg_mask = (data & 0xFF);
            break;

        case 0xBE: /* VDP DATA */
            vdp_data_w(data);
            break;

        case 0xBD: /* VDP CTRL */ 
        case 0xBF:
            vdp_ctrl_w(data);
            break;
        case 0x3F: /* TERRITORY CTRL. */
             sms.port_3F = ((data & 0x80) | (data & 0x20) << 1) & 0xC0;
            if(sms.country == TYPE_DOMESTIC) sms.port_3F ^= 0xC0;
            break;
    }
}


/* Read from an I/O port */
int cpu_readport(int port)
{
    byte temp = 0xFF;

    switch(port & 0xFF)
    {
        case 0x01: /* GG SIO */
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x05:
            return (0x00);
    
        case 0x7E: /* V COUNTER */
            return (vdp_vcounter_r());
            break;
    
        case 0x7F: /* H COUNTER */
            return (vdp_hcounter_r());
            break;
    
        case 0x00: /* INPUT #2 */
            temp = 0xFF;
            if(input.system & INPUT_START) temp &= ~0x80;
            if(sms.country == TYPE_DOMESTIC) temp &= ~0x40;
            return (temp);
    
        case 0xC0: /* INPUT #0 */  
        case 0xDC:
            temp = 0xFF;
            if(input.pad[0] & INPUT_UP)      temp &= ~0x01;
            if(input.pad[0] & INPUT_DOWN)    temp &= ~0x02;
            if(input.pad[0] & INPUT_LEFT)    temp &= ~0x04;
            if(input.pad[0] & INPUT_RIGHT)   temp &= ~0x08;
            if(input.pad[0] & INPUT_BUTTON2) temp &= ~0x10;
            if(input.pad[0] & INPUT_BUTTON1) temp &= ~0x20;
            if(input.pad[1] & INPUT_UP)      temp &= ~0x40;
            if(input.pad[1] & INPUT_DOWN)    temp &= ~0x80;
            return (temp);
    
        case 0xC1: /* INPUT #1 */
        case 0xDD:
            temp = 0xFF;
            if(input.pad[1] & INPUT_LEFT)    temp &= ~0x01;
            if(input.pad[1] & INPUT_RIGHT)   temp &= ~0x02;
            if(input.pad[1] & INPUT_BUTTON2) temp &= ~0x04;
            if(input.pad[1] & INPUT_BUTTON1) temp &= ~0x08;
            if(input.system & INPUT_SOFT_RESET) temp &= ~0x10;
            return ((temp & 0x3F) | (sms.port_3F & 0xC0));

        case 0xBE: /* VDP DATA */
            return (vdp_data_r());
    
        case 0xBD:
        case 0xBF: /* VDP CTRL */
            return (vdp_ctrl_r());

        case 0xF2: /* YM2413 DETECT */
            if(sms.use_fm) return (sms.port_F2);
            break;
    }
    return (0xFF);     
}


void sms_mapper_w(int address, int data)
{
    /* Calculate ROM page index */
    byte page = (data % cart.pages);

    /* Save frame control register data */
    sms.fcr[address] = data;

    switch(address)
    {
        case 0:
            if(data & 8)
            {
                sms.save = 1;
                /* Page in ROM */
                cpu_readmap[4]  = &sms.sram[(data & 4) ? 0x4000 : 0x0000];
                cpu_readmap[5]  = &sms.sram[(data & 4) ? 0x6000 : 0x2000];
                cpu_writemap[4] = &sms.sram[(data & 4) ? 0x4000 : 0x0000];
                cpu_writemap[5] = &sms.sram[(data & 4) ? 0x6000 : 0x2000];
            }
            else
            {
                /* Page in RAM */
                cpu_readmap[4]  = &cart.rom[((sms.fcr[3] % cart.pages) << 14) + 0x0000];
                cpu_readmap[5]  = &cart.rom[((sms.fcr[3] % cart.pages) << 14) + 0x2000];
                cpu_writemap[4] = sms.dummy;
                cpu_writemap[5] = sms.dummy;
            }
            break;

        case 1:
            cpu_readmap[0] = &cart.rom[(page << 14) + 0x0000];
            cpu_readmap[1] = &cart.rom[(page << 14) + 0x2000];
            break;

        case 2:
            cpu_readmap[2] = &cart.rom[(page << 14) + 0x0000];
            cpu_readmap[3] = &cart.rom[(page << 14) + 0x2000];
            break;

        case 3:
            if(!(sms.fcr[0] & 0x08))
            {
                cpu_readmap[4] = &cart.rom[(page << 14) + 0x0000];
                cpu_readmap[5] = &cart.rom[(page << 14) + 0x2000];
            }
            break;
    }
}


int sms_irq_callback(int param)
{
    return (0xFF);
}

