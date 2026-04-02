#include <stdint.h>

extern void setGdt(uint16_t limit, uint32_t base);
extern void reloadSegments(void);
extern void setIdt(uint16_t limit, uint32_t base);

struct gdt_ptr{
  uint16_t limit;
  uint16_t base;
} __attribute__((packed));

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_mid;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed));

struct gdt_entry gdt[3];


//struct idt_ptr{
//  uint16_t limit;
//  uint32_t base;
//} __attribute__((packed));

//struct idt_entry
//{
//    unsigned short base_lo;
//    unsigned short sel;        /* Our kernel segment goes here! o seg.sel da gdt q a cpu vai carregar no CS antes de chamar ISR*/
//    unsigned char always0;     /* This will ALWAYS be set to 0! */
//    unsigned char flags;       /* Set using the above table! */
//    unsigned short base_hi;
//} __attribute__((packed));

//struct idt_entry idt[256];
//struct idt_ptr idtp;

void gdt_set_entry(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[i].base_low    = base & 0xFFFF;
    gdt[i].base_mid    = (base >> 16) & 0xFF;
    gdt[i].base_high   = (base >> 24) & 0xFF;
    gdt[i].limit_low   = limit & 0xFFFF;
    gdt[i].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    gdt[i].access      = access;
}

void gdt_init() {
    gdt_set_entry(0, 0, 0,          0x00, 0x00); /* null */
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* code */
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* data */

    setGdt(sizeof(gdt) - 1, (uint32_t)gdt);
    reloadSegments();
}
