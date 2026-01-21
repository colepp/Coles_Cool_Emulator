#include "opcodes.h"


uint8_t fetch(CPU *cpu,MemoryBus *bus){
    return bus_read(cpu->PC++,bus);
}

Opcode decode(uint8_t b){
    return opcode_table[b];
}


void adc_imm(CPU *cpu, MemoryBus *bus){
    uint8_t imm_value = fetch(cpu,bus);
    uint16_t result =  imm_value +  cpu->A + (cpu->P & CARRY);
    update_flags_adc(cpu,result,imm_value);
    cpu->A = (uint8_t) result;
}

void adc_zp(CPU *cpu, MemoryBus *bus){
    uint8_t addr = fetch(cpu,bus);
    uint8_t zp_value = bus_read(addr,bus);
    uint16_t result = zp_value + cpu->A + (cpu->P & CARRY);
    update_flags_adc(cpu,result,zp_value);
    cpu->A = (uint8_t) result;
}

void adc_zp_x(CPU *cpu, MemoryBus *bus){
    uint8_t zp_base = fetch(cpu,bus);
    uint8_t zp_value = bus_read(WRAP_ADD(zp_base,cpu->X,ZP_SIZE),bus);
    uint16_t result =  zp_value + cpu->A + (cpu->P & CARRY);
    update_flags_adc(cpu,result,zp_value);
    cpu->A = (uint8_t) result;
}

void adc_abs(CPU *cpu,MemoryBus *bus){
    uint16_t abs_addr = BUILD_FULL_ADDRESS(fetch(cpu,bus),fetch(cpu,bus));
    uint8_t abs_value = bus_read(abs_addr,bus);
    uint16_t result = abs_value + cpu->A + (cpu->A & CARRY);
    update_flags_adc(cpu,result,abs_value);
}

void adc_abs_x(CPU *cpu,MemoryBus *bus){
    uint16_t abs_addr = (BUILD_FULL_ADDRESS(fetch(cpu,bus),fetch(cpu,bus))) + cpu->X;
    uint8_t abs_value = bus_read(abs_addr,bus);
    uint16_t result = abs_value + cpu->A + (cpu->A & CARRY);
    update_flags_adc(cpu,result,abs_value);
}

void adc_abs_y(CPU *cpu,MemoryBus *bus){
    uint16_t abs_addr = (BUILD_FULL_ADDRESS(fetch(cpu,bus),fetch(cpu,bus))) + cpu->Y;
    uint8_t abs_value = bus_read(abs_addr,bus);
    uint16_t result = abs_value + cpu->A + (cpu->A & CARRY);
    update_flags_adc(cpu,result,abs_value);
}

void adc_indr_x(CPU *cpu, MemoryBus *bus){
    uint16_t indr_addr = BUILD_FULL_ADDRESS(bus_read(cpu->X,bus),bus_read((cpu->X + 1),bus));
    uint8_t indr_value = bus_read(indr_addr,bus);
    uint16_t result = indr_value + cpu->A + (cpu->A & CARRY);
    update_flags_adc(cpu,result,indr_value);
}

void adc_indr_x(CPU *cpu, MemoryBus *bus){
    uint16_t indr_addr = BUILD_FULL_ADDRESS(bus_read(cpu->Y,bus),bus_read((cpu->X + 1),bus));
    uint8_t indr_value = bus_read(indr_addr,bus);
    uint16_t result = indr_value + cpu->A + (cpu->A & CARRY);
    update_flags_adc(cpu,result,indr_value);
}


void update_flags_adc(CPU *cpu, uint16_t result,uint8_t operand){
    if(result == 0){
        cpu->P |= ZERO;
    }else{
        cpu->P &= ~ZERO; 
    }

    if (result > 0xFF){
        cpu->P |= CARRY;
    }else{
        cpu->P &= ~CARRY;
    }

    if ((result ^ cpu->A) & (result ^ operand) & 0x80){
        cpu->P |= OVERFLOW;
    } else{
        cpu->P &= ~OVERFLOW;
    }

    if (result & 0x80 /*bit 7*/){
        cpu->P |= NEGATIVE;
    }else{
        cpu->P &= ~NEGATIVE;
    }
}




void clc(CPU *cpu,MemoryBus *bus){
    if(cpu->P & CARRY){
        cpu->P ^= CARRY;
    }
}

void cld(CPU *cpu,MemoryBus *bus){
    if(cpu->P & DECIMAL){
        cpu->P ^= DECIMAL;
    }
}
void cli(CPU *cpu,MemoryBus *bus){
    if(cpu->P & INTURRUPT){
        cpu->P ^= INTURRUPT;
    }
}
void clv(CPU *cpu,MemoryBus *bus){
    if(cpu->P & OVERFLOW){
        cpu->P ^= OVERFLOW;
    }
}
