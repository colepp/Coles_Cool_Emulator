#ifndef CARTRIDGE_H
#define CARTRIDGE_H
#include "../general/units.h"
#include <stdlib.h>
#include <stdio.h>

// Cartrige info can be found https://www.nesdev.org/wiki/INES



typedef struct {
    size_t PRG_size;
    size_t CHR_size;
    uint8_t flags6; // (Mapper,mirroring,battery,trainer)
    uint8_t flags7; // (Mapper, VS/playchoice,NES 2.0) 
    uint8_t *PRG_data;
    uint8_t *CHR_data;
    uint8_t *cartridge_ram;

} Cartridge;


Cartridge *build_cartrige(
    size_t PRG_size,
    size_t CHR_size,
    uint8_t flags6,
    uint8_t flags7);

void display_information(Cartridge *c);

#endif