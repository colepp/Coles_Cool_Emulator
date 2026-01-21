#include "./memory_manager.h"

MemoryBus *init_bus(Cartridge *c){
    MemoryBus *memory_bus = (MemoryBus *)(sizeof(MemoryBus));
    if(memory_bus){
        uint8_t *cpu_ram = malloc(sizeof(uint8_t) * CPU_RAM_SIZE);
        if(cpu_ram){
            memory_bus->cartridge = c;
            memory_bus->cpu_ram = cpu_ram;
            return cpu_ram;
        }
        free(memory_bus);
    }
    return NULL;
}

uint8_t bus_read(const uint16_t addr,MemoryBus* bus){
    if(addr >= INTERNAL_S && addr <= INTERNAL_E){
        uint16_t mirror_addr = CPU_MIRROR(addr);
        return bus->cpu_ram[mirror_addr];
    }
    else if(addr >= PPU_REGISTER_S && addr <= PPU_REGISTER_E){
        uint16_t mirror_add = PPU_MIRROR(addr);
        return 0;
    }
    else if(addr >= CARTRIDGE_RAM_S && addr <= CARTRIDGE_RAM_E ){
        return bus->cartridge->cartridge_ram[addr - CARTRIDGE_RAM_S];
    }
    else if(addr >= PRG_BANK_0_S && addr <= PRG_BANK_0_E){
        uint16_t mirror_addr = PRG_MIRROR((addr - PRG_BANK_0_S),bus->cartridge->PRG_size);
        return bus->cartridge->PRG_data[mirror_addr];
    }
    else return 0;
}


void bus_write(const uint16_t addr,const uint8_t value,MemoryBus* bus){
    if(addr >= INTERNAL_S && addr <= INTERNAL_E){
        uint16_t mirror_addr = CPU_MIRROR(addr);
        bus->cpu_ram[mirror_addr] = value;
    }
    else if(addr >= PPU_REGISTER_S && addr <= PPU_REGISTER_E){
        return;
    }
    else if(addr >= CARTRIDGE_RAM_S && addr <= CARTRIDGE_RAM_E ){
        bus->cartridge->cartridge_ram[addr - CARTRIDGE_RAM_S] = value;
    }
    else if(addr >= PRG_BANK_0_S && addr <= PRG_BANK_0_E){
        return;
    }
}