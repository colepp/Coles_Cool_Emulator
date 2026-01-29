#ifndef MEMORY_MANAGER_H

#define MEMORY_MANAGER_H
#include "cartridge.h"



#define INTERNAL_S 0x0000
#define INTERNAL_E 0x1FFF


#define PPU_REGISTER_S 0x2000
#define PPU_REGISTER_E 0x3FFF

#define APU_IO_S 0x4000
#define APU_IO_E 0x401F

#define CARTRIDGE_RAM_S 0x6000
#define CARTRIDGE_RAM_E 0x7FFF

#define PRG_BANK_0_S 0x8000
#define PRG_BANK_0_E 0xBFFF

#define  NMI_VEC_LOW
#define  NMI_VEC_HIGH

#define RESET_VEC_LOW 0xFFFC
#define RESET_VEC_HIGH 0xFFFD

#define BRK_IRQ_VEC_LOW 0xFFFE
#define BRK_IRQ_VEC_HIGH 0xFFFF



#define CPU_MIRROR(x) ((x) % CPU_RAM_SIZE)
#define PPU_MIRROR(x) (PPU_REGISTER_S + ((x) - PPU_REGISTER_S) % 8)
#define PRG_MIRROR(x,y) (((x) - PRG_BANK_0_S) % (y))

typedef struct {
    uint8_t *cpu_ram;
    Cartridge *cartridge;
} MemoryBus;

MemoryBus *init_bus(Cartridge *c);

uint8_t bus_read(const uint16_t addr,MemoryBus* bus);
void bus_write(const uint16_t addr,const uint8_t value,MemoryBus* bus);


#endif