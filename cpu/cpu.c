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

    uint8_t zp_base = fetch(cpu,bus);
    uint8_t zp_value = bus_read(zp_base,bus);

    uint16_t result = zp_value + cpu->A + (cpu->P & CARRY);

    update_flags_adc(cpu,result,zp_value);
    cpu->A = (uint8_t) result;
}

void adc_zp_x(CPU *cpu, MemoryBus *bus){

    uint8_t zp_base = fetch(cpu,bus);
    uint8_t zp_value = bus_read(WRAP_ADD(zp_base,cpu->X,ZP_SIZE),bus);

    uint16_t result =  zp_value + cpu->A + (cpu->P & :CARRY);

    update_flags_adc(cpu,result,zp_value);
    cpu->A = (uint8_t) result;
}

void adc_abs(CPU *cpu,MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = BUILD_FULL_ADDRESS(low,high);
    uint8_t abs_value = bus_read(abs_addr,bus);

    uint16_t result = abs_value + cpu->A + (cpu->A & CARRY);

    update_flags_adc(cpu,result,abs_value);
    cpu->A = (uint8_t) result;
}

void adc_abs_x(CPU *cpu,MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t abs_value = bus_read(abs_addr,bus);

    uint16_t result = abs_value + cpu->A + (cpu->A & CARRY);

    update_flags_adc(cpu,result,abs_value);
    cpu->A = (uint8_t) result;
}

void adc_abs_y(CPU *cpu,MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->Y;
    uint8_t abs_value = bus_read(abs_addr,bus);

    uint16_t result = abs_value + cpu->A + (cpu->A & CARRY);

    update_flags_adc(cpu,result,abs_value);
    cpu->A = (uint8_t) result;
}

void adc_indr_x(CPU *cpu, MemoryBus *bus){

    uint8_t low = cpu->X;
    uint8_t high = low + 1;


    uint16_t indr_addr = BUILD_FULL_ADDRESS(low,high);
    uint8_t indr_value = bus_read(indr_addr,bus);

    uint16_t result = indr_value + cpu->A + (cpu->A & CARRY);

    update_flags_adc(cpu,result,indr_value);
    cpu->A = (uint8_t) result;
}

void adc_indr_y(CPU *cpu, MemoryBus *bus){

    uint8_t low = cpu->Y;
    uint8_t high = low + 1;

    uint16_t indr_addr = BUILD_FULL_ADDRESS(low,high,bus));
    uint8_t indr_value = bus_read(indr_addr,bus);

    uint16_t result = indr_value + cpu->A + (cpu->A & CARRY);

    update_flags_adc(cpu,result,indr_value);
    cpu->A = (uint8_t) result;
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

void and_imm(CPU *cpu, MemoryBus *bus) {

  uint8_t imm_value = fetch(cpu,bus);

  uint8_t result = cpu->A & imm_value;

  update_flags_and(cpu,result);
  cpu->A = result;

}

void and_zp(CPU *cpu, MemoryBus *bus) {

  uint8_t zp_value = bus_read(fetch(cpu,bus),bus);

  uint8_t result = cpu->A & zp_value;

  update_flags_and(cpu,result);
  cpu->A = result;
}

void and_zp_x(CPU *cpu, MemoryBus *bus){

  uint8_t zp_value = bus_read(WRAP_ADD(cpu->X,fetch(cpu,bus),ZP_SIZE),bus);

  uint8_t result = cpu->A & zp_value;

  update_flags_and(cpu,result);
  cpu->A = result;
}

void and_abs(CPU *cpu, MemoryBus *bus){

  uint8_t low = fetch(cpu,bus);
  uint8_t high = fetch(cpu,bus);

  uint16_t abs_addr = BUILD_FULL_ADDRESS(low,high);
  uint8_t abs_value = bus_read(abs_addr,bus);

  uint8_t result = cpu->A & abs_value;

  update_flags_and(cpu,result);
  cpu->A = result;
}

void and_abs_x(CPU *cpu, MemoryBus *bus){

  uint8_t low = fetch(cpu,bus);
  uint8_t high = fetch(cpu,bus);

  uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
  uint8_t abs_value = bus_read(abs_addr,bus);

  uint8_t result = cpu->A & abs_value;

  update_flags_and(cpu,result);
  cpu->A = result;
}

void and_indr_x(CPU *cpu, MemoryBus *bus){

  uint8_t low = cpu->X;
  uint8_t high = low + 1;

  uint16_t indr_addr = BUILD_FULL_ADDRESS(low,high);
  uint8_t indr_value = bus_read(indr_addr,bus);

  uint8_t result = cpu->A & indr_value;

  update_flags_and(result,cpu);
  cpu->A = result;

}

void and_indr_y(CPU *cpu, MemoryBus *bus){

  uint8_t low = cpu->Y;
  uint8_t high = low + 1;

  uint16_t indr_addr = BUILD_FULL_ADDRESS(low,high);
  uint8_t indr_value = bus_read(indr_addr,bus);

  uint8_t result = cpu->A & indr_value;

  update_flags_and(result,cpu);
  cpu->A = result;

}


void update_flags_and(CPU *cpu,uint8_t result){
  if (result == 0) {
    cpu->P |= ZERO;
  }else {
    cpu->P &= ~ZERO;
  }

  if (result & 0x80 ) {
    cpu->P |= NEGATIVE;
  }else {
    cpu-> &= ~NEGATIVE;
  }
  cpu->A = result;

}

void asl_acc(CPU *cpu, uint8_t result){

  uint8_t result = cpu->A << 1;

  update_flags_asl(cpu,result,cpu->A);
  cpu->A = result;


}

void asl_zp(cpu *cpu, MemoryBus *bus){

  uint8_t zp_addr = fetch(cpu,bus);
  uint8_t zp_value = bus_read(zp_addr,bus);

  uint8_t result = zp_value << 1;

  update_flags_asl(cpu,result,zp_value);
  bus_write(result,zp_addr,bus);
}


void update_flags_asl(CPU *cpu,uint8_t result, uint8_t operand){

  if(operand & 0x80){
    cpu->P |= CARRY;
  }else{
    cpu->P &= ~CARRY;
  }

  if(result & 0x80){
    cpu->P |= NEGATIVE;
  }else{
    cpu->P &= ~NEGATIVE;
  }

  if(result == 0){
    cpu->P |= ZERO;
  }else{
    cpu->P &= ~ZERO;
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
