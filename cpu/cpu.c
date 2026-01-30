#include "./opcodes.h"

CPU *init_cpu(){
    CPU *new_cpu = malloc(sizeof(CPU));
    if (new_cpu) return new_cpu;
    return NULL;

}

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

    uint16_t result =  zp_value + cpu->A + (cpu->P & CARRY);

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

    uint8_t zp_addr = fetch(cpu,bus);

    uint8_t low = bus_read(zp_addr,bus);
    uint8_t high = bus_read(WRAP_ADD(1,zp_addr,ZP_SIZE),bus);


    uint16_t indr_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t indr_value = bus_read(indr_addr,bus);

    uint16_t result = indr_value + cpu->A + (cpu->A & CARRY);

    update_flags_adc(cpu,result,indr_value);
    cpu->A = (uint8_t) result;
}

void adc_indr_y(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = fetch(cpu,bus);

    uint8_t low = bus_read(zp_addr,bus);
    uint8_t high = bus_read(WRAP_ADD(1,zp_addr,ZP_SIZE),bus);

    uint16_t indr_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->Y;
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

    uint8_t zp_addr = fetch(cpu,bus);

    uint8_t low = bus_read(zp_addr,bus);
    uint8_t high = bus_read(WRAP_ADD(1,zp_addr,ZP_SIZE),bus);

    uint16_t indr_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t indr_value = bus_read(indr_addr,bus);

  uint8_t result = cpu->A & indr_value;

  update_flags_and(cpu,result);
  cpu->A = result;

}

void and_indr_y(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = fetch(cpu,bus);

    uint8_t low = bus_read(zp_addr,bus);
    uint8_t high = bus_read(WRAP_ADD(1,zp_addr,ZP_SIZE),bus);

    uint16_t indr_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->Y;
    uint8_t indr_value = bus_read(indr_addr,bus);
  uint8_t result = cpu->A & indr_value;

  update_flags_and(cpu,result);
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
    cpu->P &= ~NEGATIVE;
  }
  cpu->A = result;

}

void asl_acc(CPU *cpu, MemoryBus *bus){

  uint8_t result = cpu->A << 1;

  update_flags_asl(cpu,result,cpu->A);
  cpu->A = result;


}

void asl_zp(CPU *cpu, MemoryBus *bus){

  uint8_t zp_addr = fetch(cpu,bus);
  uint8_t zp_value = bus_read(zp_addr,bus);

  uint8_t result = zp_value << 1;

  update_flags_asl(cpu,result,zp_value);
  bus_write(zp_addr,result,bus);
}

void asl_zp_x(CPU *cpu, MemoryBus *bus){
    uint8_t  zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->X,ZP_SIZE);
    uint8_t  zp_value = bus_read(zp_addr,bus);

    uint8_t result = zp_value << 1;
    update_flags_asl(cpu,result,zp_value);
    bus_write(zp_addr,result,bus);
}

void asl_abs(CPU *cpu, MemoryBus *bus){
    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = BUILD_FULL_ADDRESS(low,high);
    uint8_t  abs_value = bus_read(abs_addr,bus);


    uint8_t result = abs_value << 1;
    update_flags_asl(cpu,result,abs_value);
    bus_write(abs_addr,result,bus);

}

void asl_abs_x(CPU *cpu, MemoryBus *bus){
        uint8_t low = fetch(cpu,bus);
        uint8_t high = fetch(cpu,bus);

        uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
        uint8_t  abs_value = bus_read(abs_addr,bus);


        uint8_t result = abs_value << 1;
        update_flags_asl(cpu,result,abs_value);
        bus_write(abs_addr,result,bus);
};

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

void bcc(CPU *cpu, MemoryBus *bus){
    int8_t memory_val = (int8_t) fetch(cpu,bus);
    if(!(cpu->P & CARRY)){
        cpu->PC += memory_val;
    }
}

void bcs(CPU *cpu, MemoryBus *bus){
    int8_t memory_val = (int8_t) fetch(cpu,bus);
    if(cpu->P & CARRY){
        cpu->PC += memory_val;
    }
}

void beq(CPU *cpu, MemoryBus *bus){
    int8_t memory_val = (int8_t) fetch(cpu,bus);
    if(cpu->P & ZERO){
        cpu->PC += memory_val;
    }
}

void bit_zp(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = fetch(cpu,bus);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint8_t  result = cpu->A & zp_value;
    update_flags_bit(cpu,result,zp_value);
}

void bit_abs(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = BUILD_FULL_ADDRESS(low,high);
    uint8_t  abs_value = bus_read(abs_addr,bus);

    uint8_t  result = cpu->A & abs_value;
    update_flags_bit(cpu,result,abs_value);

}

void update_flags_bit(CPU *cpu, uint8_t result, uint8_t memory){

    if(result == 0){
        cpu->P |= ZERO;
    }else {
        cpu->P &= ~ ZERO;
    }

    if(memory & 0x40){
        cpu->P |= OVERFLOW;

    }else{
        cpu->P &= ~OVERFLOW;
    }

    if(memory & 0x80){
        cpu->P |= NEGATIVE;
    }else{
        cpu->P &= ~NEGATIVE;
    }

}

void bmi(CPU *cpu,MemoryBus *bus){
    int8_t memory_val = (int8_t) fetch(cpu,bus);
    if(cpu->P & NEGATIVE){
        cpu->PC += memory_val;
    }
}

void bne(CPU *cpu,MemoryBus *bus){
    int8_t memory_val = (int8_t) fetch(cpu,bus);
    if(!(cpu->P & ZERO)){
        cpu->PC += memory_val;
    }
}

void bpl(CPU *cpu,MemoryBus *bus){
    int8_t memory_val = (int8_t) fetch(cpu,bus);
    if(!(cpu->P & NEGATIVE)){
        cpu->PC += memory_val;
    }
}

void brk(CPU *cpu, MemoryBus *bus){

    bus_write(STACK_OFFSET(cpu->S--), (cpu->PC) >> 8,bus);
    bus_write(STACK_OFFSET(cpu->S--),(cpu->PC),bus);
    bus_write(STACK_OFFSET(cpu->S--),(cpu->P | B_FLAG),bus);
    cpu->P |= INTURRUPT;
    cpu->PC = BUILD_FULL_ADDRESS(bus_read(BRK_IRQ_VEC_LOW,bus), bus_read(BRK_IRQ_VEC_HIGH,bus));

}

void bvc(CPU *cpu, MemoryBus *bus){
    int8_t memory_val = (int8_t) fetch(cpu,bus);
    if(!(cpu->P & OVERFLOW)){
        cpu->PC += memory_val;
    }
}

void bvs(CPU *cpu, MemoryBus *bus){
    int8_t memory_val = (int8_t) fetch(cpu,bus);
    if((cpu->P & OVERFLOW)){
        cpu->PC += memory_val;
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


void cmp_imm(CPU *cpu, MemoryBus *bus){

    uint8_t imm_value = fetch(cpu,bus);

    uint8_t result = cpu->A - imm_value;
    update_flags_cmp(cpu,result,imm_value);
}

void cmp_zp(CPU *cpu, MemoryBus *bus){
    uint8_t  zp_addr = fetch(cpu,bus);
    uint8_t  zp_value = bus_read(zp_addr,bus);

    uint8_t  result = cpu->A - zp_value;
    update_flags_cmp(cpu,result,zp_value);
}

void cmp_zp_x(CPU *cpu, MemoryBus *bus){

    uint8_t  zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->X,ZP_SIZE);
    uint8_t  zp_value = bus_read(zp_addr,bus);

    uint8_t  result = cpu->A - zp_value;
    update_flags_cmp(cpu,result,zp_value);
}

void cmp_abs(CPU *cpu, MemoryBus *bus){
    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = BUILD_FULL_ADDRESS(low,high);
    uint8_t  abs_value = bus_read(abs_addr,bus);

    uint8_t  result = cpu->A - abs_value;
    update_flags_cmp(cpu,result,abs_value);

}

void cmp_abs_x(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t  abs_value = bus_read(abs_addr,bus);

    uint8_t  result = cpu->A - abs_value;
    update_flags_cmp(cpu,result,abs_value);

}

void cmp_abs_y(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->Y;
    uint8_t  abs_value = bus_read(abs_addr,bus);

    uint8_t  result = cpu->A - abs_value;
    update_flags_cmp(cpu,result,abs_value);

}

void cmp_indr_x(CPU *cpu, MemoryBus *bus){
    uint8_t zp_addr = fetch(cpu,bus);

    uint8_t low = bus_read(zp_addr,bus);
    uint8_t high = bus_read(WRAP_ADD(1,zp_addr,ZP_SIZE),bus);

    uint16_t indr_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->Y;
    uint8_t indr_value = bus_read(indr_addr,bus);

    uint8_t  result = cpu->A - indr_value;
    update_flags_cmp(cpu,result,indr_value);



}

void cmp_indr_y(CPU *cpu, MemoryBus *bus){
    uint8_t zp_addr = fetch(cpu,bus);

    uint8_t low = bus_read(zp_addr,bus);
    uint8_t high = bus_read(WRAP_ADD(1,zp_addr,ZP_SIZE),bus);

    uint16_t indr_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->Y;
    uint8_t indr_value = bus_read(indr_addr,bus);

    uint8_t  result = cpu->A - indr_value;
    update_flags_cmp(cpu,result,indr_value);



}

void cpx_imm(CPU *cpu, MemoryBus *bus){
    uint8_t imm_value = fetch(cpu,bus);

    uint8_t result = cpu->X - imm_value;
    update_flags_cmp(cpu,result,imm_value);
}

void cpx_zp(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = fetch(cpu,bus);
    uint8_t zp_value = bus_read(zp_addre,bus);

    uint8_t result = cpu->X - zp_value;
    update_flags_cmp(cpu,result,zp_value);
}

void cpx_abs(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = BUILD_FULL_ADDRESS(low,high);
    uint8_t abs_value = bus_read(abs_addr,bus);


    uint8_t result = cpu->X - abs_value;
    update_flags_cmp(cpu,result,abs_value);
}

void cpy_imm(CPU *cpu, MemoryBus *bus){
    uint8_t imm_value = fetch(cpu,bus);

    uint8_t result = cpu->Y - imm_value;
    update_flags_cmp(cpu,result,imm_value);
}

void cpy_zp(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = fetch(cpu,bus);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint8_t result = cpu->Y - zp_value;
    update_flags_cmp(cpu,result,zp_value);
}

void cpy_abs(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = BUILD_FULL_ADDRESS(low,high);
    uint8_t abs_value = bus_read(abs_addr,bus);


    uint8_t result = cpu->Y - abs_value;
    update_flags_cmp(cpu,result,abs_value);
}

void update_flags_cmp(CPU *cpu,uint8_t result,uint8_t memory){

    if (cpu->A >= memory) {
        cpu->P |= CARRY;
    }else {
        cpu->P &= ~CARRY;
    }

    if (cpu->A == memory) {
        cpu->P |= ZERO;
    }else {
        cpu->P &= ~ZERO;
    }


    if (result & 0x80) {
        cpu->P |= NEGATIVE;
    }else {
        cpu->P &= ~NEGATIVE;
    }


}

void dec_zp(CPU *cpu, MemoryBus *bus){

    uint8_t  zp_addr = fetch(cpu,bus);
    uint8_t  zp_value = bus_read(zp_addr,bus);

    uint8_t result = zp_value - 1;
    update_flags_decrement(cpu,result);
    bus_write(zp_addr,result,bus);

}

void dec_zp_x(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->X,ZP_SIZE);
    uint8_t  zp_value = bus_read(zp_addr,bus);

    uint8_t result = zp_value - 1;
    update_flags_decrement(cpu,result);
    bus_write(zp_addr,result,bus);
}

void dec_abs(CPU *cpu, MemoryBus *bus){
    uint8_t  low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = BUILD_FULL_ADDRESS(low,high);
    uint8_t abs_value = bus_read(abs_addr,bus);

    uint8_t result = abs_value - 1;
    update_flags_decrement(cpu,result);
    bus_write(abs_addr,result,bus);
}

void dec_abs_x(CPU *cpu, MemoryBus *bus){

    uint8_t  low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t abs_value = bus_read(abs_addr,bus);

    uint8_t result = abs_value - 1;
    update_flags_decrement(cpu,result);
    bus_write(abs_addr,result,bus);
}

void dex(CPU *cpu, MemoryBus *bus){

    cpu->X--;
    update_flags_decrement(cpu,cpu->X);

}

void dey(CPU *cpu, MemoryBus *bus){
    cpu->Y--;
    update_flags_decrement(cpu,cpu->Y);
}

void update_flags_decrement(CPU *cpu,uint8_t result){
    if (result == 0){
        cpu->P |= ZERO;
    }else {
        cpu->P &= ~ZERO;
    }

    if (result & 0x80){
        cpu->P |= NEGATIVE;
    }else{
        cpu->P &= ~NEGATIVE;
    }
}

void eor_imm(CPU *cpu, MemoryBus *bus){

    uint8_t imm_value = fetch(cpu,bus);

    uint8_t result = cpu->A ^ imm_value;
    update_flags_eor(cpu,result);
    cpu->A = result;

}

void eor_zp(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = fetch(cpu,bus);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint8_t result = cpu->A ^ zp_value;
    update_flags_eor(cpu,result);
    cpu->A = result;

}

void eor_zp_x(CPU *cpu, MemoryBus *bus){

    uint8_t  zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->X,ZP_SIZE);
    uint8_t  zp_value = bus_read(zp_addr,bus);

    uint8_t result = cpu->A ^ zp_value;
    update_flags_eor(cpu,result);
    cpu->A = result;

}

void eor_abs(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high));
    uint8_t  abs_value = bus_read(abs_addr,bus);

    uint8_t result = cpu->A ^ abs_value;
    update_flags_eor(cpu,result);
    cpu->A = result;
}

void eor_abs_x(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t  abs_value = bus_read(abs_addr,bus);

    uint8_t result = cpu->A ^ abs_value;
    update_flags_eor(cpu,result);
    cpu->A = result;
}

void eor_abs_y(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->Y;
    uint8_t  abs_value = bus_read(abs_addr,bus);

    uint8_t result = cpu->A ^ abs_value;
    update_flags_eor(cpu,result);
    cpu->A = result;
}

void eor_indr_x(CPU *cpu, MemoryBus *bus){
    uint8_t zp_addr = fetch(cpu,bus);

    uint8_t low = bus_read(zp_addr,bus);
    uint8_t high = bus_read(WRAP_ADD(1,zp_addr,ZP_SIZE),bus);

    uint16_t indr_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t indr_value = bus_read(indr_addr,bus);

    uint8_t result = cpu->A ^ indr_value;
    update_flags_eor(cpu,result);
    cpu->A = result;
}

void eor_indr_y(CPU *cpu, MemoryBus *bus){
    uint8_t zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->Y,ZP_SIZE);

    uint8_t low = bus_read(zp_addr,bus);
    uint8_t high = bus_read(WRAP_ADD(1,zp_addr,ZP_SIZE),bus);

    uint16_t indr_addr = BUILD_FULL_ADDRESS(low,high);
    uint8_t  indr_value = bus_read(indr_addr,bus);

    uint8_t result = cpu->A ^ indr_value;
    update_flags_eor(cpu,result);
    cpu->A = result;
}

void update_flags_eor(CPU *cpu,uint8_t result){
    if (result == 0){
        cpu->P |= ZERO;
    }else {
        cpu->P &= ~ZERO;
    }

    if (result & 0x80){
        cpu->P |= NEGATIVE;
    }else {
        cpu->P &= ~NEGATIVE;
    }
}

void inc_zp(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = fetch(cpu,bus);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint8_t result = 1 + zp_value;
    update_flags_increment(cpu,result);
    bus_write(zp_addr,result,bus);

}

void inc_zp_x(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->X,ZP_SIZE);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint8_t result = 1 + zp_value;
    update_flags_increment(cpu,result);
    bus_write(zp_addr,result,bus);

}

void inc_abs(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = BUILD_FULL_ADDRESS(low,high);
    uint8_t  abs_value = bus_read(abs_addr,bus);


    uint8_t result = 1 + abs_value;
    update_flags_increment(cpu,result);
    bus_write(abs_addr,result,bus);

}

void inc_abs_x(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = BUILD_FULL_ADDRESS(low,high) + cpu->X;
    uint8_t  abs_value = bus_read(abs_addr,bus);


    uint8_t result = 1 + abs_value;
    update_flags_increment(cpu,result);
    bus_write(abs_addr,result,bus);

}

void inx(CPU *cpu, MemoryBus *bus){
    cpu->X++;
    update_flags_increment(cpu,cpu->X);
}

void iny(CPU *cpu, MemoryBus *bus){
    cpu->Y++;
    update_flags_increment(cpu,cpu->Y);
}

void update_flags_increment(CPU *cpu, uint8_t result){
    if(result == 0){
        cpu->P |= ZERO;
    }else{
        cpu->P &= ~ZERO;
    }

    if (result * 0x80){
        cpu->P |= NEGATIVE;
    }else{
        cpu->P &= ~NEGATIVE;
    }
}

void jmp_abs(CPU *cpu, MemoryBus *bus){
    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);
    cpu->PC = BUILD_FULL_ADDRESS(low,high);
}

void jmp_indr(CPU *cpu, MemoryBus *bus){
    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t indr_addr = BUILD_FULL_ADDRESS(low,high);

    low = bus_read(indr_addr,bus);
    high = bus_read((indr_addr & 0xFF00) | ((indr_addr + 1) & 0x00FF),bus);

    cpu->PC = BUILD_FULL_ADDRESS(low,high);
}

void jsr(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    bus_write(STACK_OFFSET(cpu->S--), (cpu->PC - 1) >> 8,bus);
    bus_write(STACK_OFFSET(cpu->S--),(cpu->PC - 1),bus);

    cpu->PC = BUILD_FULL_ADDRESS(low,high);
}

void lda_imm(CPU *cpu, MemoryBus *bus){

    uint8_t imm_value = fetch(cpu,bus);

    cpu->A = imm_value;
    update_flags_load(cpu,cpu->A);
}

void lda_zp(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = fetch(cpu,bus);
    uint8_t zp_value = bus_read(zp_addr,bus);

    cpu->A = zp_value;
    update_flags_load(cpu,cpu->A);
}

void lda_zp_x(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->X,ZP_SIZE);
    uint8_t zp_value = bus_read(zp_addr,bus);

    cpu->A = zp_value;
    update_flags_load(cpu,cpu->A);
}

void lda_abs(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high));
    uint8_t abs_value = bus_read(abs_addr,bus);


    cpu->A = abs_value;
    update_flags_load(cpu,cpu->A);
}

void lda_abs_x(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t abs_value = bus_read(abs_addr,bus);


    cpu->A = abs_value;
    update_flags_load(cpu,cpu->A);
}

void lda_abs_y(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->Y;
    uint8_t abs_value = bus_read(abs_addr,bus);


    cpu->A = abs_value;
    update_flags_load(cpu,cpu->A);
}

void lda_indr_x(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = fetch(cpu,bus);

    uint8_t low = bus_read(zp_addr,bus);
    uint8_t high = bus_read(WRAP_ADD(1,zp_addr,ZP_SIZE),bus);

    uint16_t indr_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t indr_value = bus_read(indr_addr,bus);


    cpu->A = indr_value;
    update_flags_load(cpu,cpu->A);
}

void lda_indr_y(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = fetch(cpu,bus);

    uint8_t low = bus_read(zp_addr,bus);
    uint8_t high = bus_read(WRAP_ADD(1,zp_addr,ZP_SIZE),bus);

    uint16_t indr_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->Y;
    uint8_t indr_value = bus_read(indr_addr,bus);


    cpu->A = indr_value;
    update_flags_load(cpu,cpu->A);
}

void ldx_imm(CPU *cpu,MemoryBus *bus){
    uint8_t imm_value = fetch(cpu,bus);

    cpu->X = imm_value;
    update_flags_load(cpu,cpu->X);
}

void ldx_zp(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = fetch(cpu,bus);
    uint8_t zp_value = bus_read(zp_addr,bus);

    cpu->X = zp_value;
    update_flags_load(cpu,cpu->X);
}

void ldx_zp_y(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->Y,ZP_SIZE);
    uint8_t zp_value = bus_read(zp_addr,bus);

    cpu->X = zp_value;
    update_flags_load(cpu,cpu->X);
}

void ldx_abs(CPU *cpu,MemoryBus *bus) {

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high));
    uint8_t abs_value = bus_read(abs_addr,bus);

    cpu->X = abs_value;
    update_flags_load(cpu,cpu->X);
}

void ldx_abs_y(CPU *cpu,MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->Y;
    uint8_t abs_value = bus_read(abs_addr,bus);

    cpu->X = abs_value;
    update_flags_load(cpu,cpu->X);
}

void ldy_imm(CPU *cpu,MemoryBus *bus){
    uint8_t imm_value = fetch(cpu,bus);

    cpu->Y = imm_value;
    update_flags_load(cpu,cpu->Y);
}

void ldy_zp(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = fetch(cpu,bus);
    uint8_t zp_value = bus_read(zp_addr,bus);

    cpu->Y = zp_value;
    update_flags_load(cpu,cpu->Y);
}

void ldy_zp_x(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->X,ZP_SIZE);
    uint8_t zp_value = bus_read(zp_addr,bus);

    cpu->Y = zp_value;
    update_flags_load(cpu,cpu->Y);
}

void ldy_abs(CPU *cpu,MemoryBus *bus) {

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high));
    uint8_t abs_value = bus_read(abs_addr,bus);

    cpu->Y = abs_value;
    update_flags_load(cpu,cpu->Y);
}

void ldy_abs_x(CPU *cpu,MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t abs_value = bus_read(abs_addr,bus);

    cpu->Y = abs_value;
    update_flags_load(cpu,cpu->Y);
}

void update_flags_load(CPU *cpu, uint8_t result){
        if(result == 0){
            cpu->P |= ZERO;
        }else{
            cpu->P &= ~ZERO;
        }

        if (result * 0x80){
            cpu->P |= NEGATIVE;
        }else{
            cpu->P &= ~NEGATIVE;
        }
    }

void lsr_acc(CPU *cpu, MemoryBus *bus){

    uint8_t result = cpu->A >> 1;
    update_flags_lsr(cpu,result,cpu->A);
    cpu->A = result;
}

void lsr_zp(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = fetch(cpu,bus);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint8_t result = zp_addr >> 1;
    update_flags_lsr(cpu,result,zp_value);
    bus_write(zp_addr,result,bus);
}

void lsr_zp_x(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->X,ZP_SIZE);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint8_t result = zp_addr >> 1;
    update_flags_lsr(cpu,result,zp_value);
    bus_write(zp_addr,result,bus);
}

void lsr_abs(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high));
    uint8_t abs_value = bus_read(abs_addr,bus);

    uint8_t result = abs_addr >> 1;
    update_flags_lsr(cpu,result,abs_value);
    bus_write(abs_addr,result,bus);
}

void lsr_abs_x(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t abs_value = bus_read(abs_addr,bus);

    uint8_t result = abs_addr >> 1;
    update_flags_lsr(cpu,result,abs_value);
    bus_write(abs_addr,result,bus);

}

void update_flags_lsr(CPU *cpu,uint8_t result,uint8_t operand){

    if(operand & 0x01){
        cpu->P |= CARRY;
    }else{
        cpu->P &= ~CARRY;
    }

    if(result == 0){
        cpu->P |= ZERO;
    }else{
        cpu->P &= ~ZERO;
    }

    cpu->P &= ~NEGATIVE;
}

void nop(CPU *cpu, MemoryBus *bus){}

void ora_imm(CPU *cpu, MemoryBus *bus){

    uint8_t imm_value = fetch(cpu,bus);

    uint8_t result = cpu->A | imm_value;

    update_flags_ora(cpu,result);
    cpu->A = result;
}

void ora_zp(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = fetch(cpu,bus);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint8_t result = cpu->A | zp_value;
    update_flags_ora(cpu,result);
    cpu->A = result;
}

void ora_zp_x(CPU *cpu, MemoryBus *bus) {
    uint8_t zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->X,ZP_SIZE);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint8_t result = cpu->A | zp_value;

    update_flags_ora(cpu,result);
    bus_write(zp_addr,result,bus);
}

void ora_abs(CPU *cpu, MemoryBus *bus) {
    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high));
    uint8_t abs_value = bus_read(abs_addr,bus);

    uint8_t result = cpu->A | abs_value;
    update_flags_ora(cpu,result);
    bus_write(abs_addr,result,bus);
}

void ora_abs_x(CPU *cpu, MemoryBus *bus) {
    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t abs_value = bus_read(abs_addr,bus);

    uint8_t result = cpu->A | abs_value;
    update_flags_ora(cpu,result);
    bus_write(abs_addr,result,bus);
}

void ora_abs_y(CPU *cpu, MemoryBus *bus) {
    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->Y;
    uint8_t abs_value = bus_read(abs_addr,bus);

    uint8_t result = cpu->A | abs_value;
    update_flags_ora(cpu,result);
    bus_write(abs_addr,result,bus);
}

void ora_indr_x(CPU *cpu,MemoryBus *bus) {
    uint8_t zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->Y,ZP_SIZE);

    uint8_t low = bus_read(zp_addr,bus);
    uint8_t high = bus_read(WRAP_ADD(1,zp_addr,ZP_SIZE),bus);

    uint16_t indr_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->Y;
    uint8_t indr_value = bus_read(indr_addr,bus);

    uint8_t result = cpu->A | indr_value;
    update_flags_ora(cpu,result);
    bus_write(indr_addr,result,bus);

}

void ora_indr_y(CPU *cpu, MemoryBus *bus) {
    uint8_t zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->,ZP_SIZE);

    uint8_t low = bus_read(zp_addr,bus);
    uint8_t high = bus_read(WRAP_ADD(1,zp_addr,ZP_SIZE),bus);

    uint16_t indr_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t indr_value = bus_read(indr_addr,bus);

    uint8_t result = cpu->A | indr_value;
    update_flags_ora(cpu,result);
    bus_write(indr_addr,result,bus);
}

void pha(CPU *cpu, MemoryBus *bus) {
    bus_write(STACK_OFFSET(cpu->S--),cpu->A,bus);
}

void php(CPU *cpu, MemoryBus *bus) {
    bus_write(STACK_OFFSET(cpu->S--),cpu->P | B_FLAG | ONE_FLAG,bus);
}

void pla(CPU *cpu,MemoryBus *bus) {
    cpu->A = bus_read(STACK_OFFSET(++cpu->S),bus);

    if (cpu->A == 0) {
        cpu->P |= ZERO;
    }else {
        cpu->P &= ~ZERO;
    }

    if (cpu->A & 0x80) {
        cpu->P |= NEGATIVE;
    }else {
        cpu->P &= ~NEGATIVE;
    }
}

void plp(CPU *cpu, MemoryBus *bus) {
    cpu->P = bus_read(STACK_OFFSET(++cpu->S),bus);
    cpu->P |= ONE_FLAG;
    cpu->P &= ~B_FLAG;
}

void rol_acc(CPU *cpu, MemoryBus *bus){

    uint8_t result = ((cpu->P & CARRY) | (cpu->A << 1));
    update_flags_rotate(cpu,result,cpu->A);
    cpu->A = result;

}

void rol_zp(CPU *cpu, MemoryBus *bus){
    uint8_t zp_addr = fetch(cpu,bus);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint8_t result = ((cpu->P & CARRY) | (zp_value << 1));
    update_flags_rotate(cpu,result,zp_value);
    bus_write(zp_addr,result,bus);

}

void rol_zp_x(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->X,ZP_SIZE);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint8_t result = ((cpu->P & CARRY) | (zp_value << 1));
    update_flags_rotate(cpu,result,zp_value);
    bus_write(zp_addr,result,bus);

}

void rol_abs(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high));
    uint8_t  abs_value = bus_read(abs_addr,bus);

    uint8_t result = ((cpu->P & CARRY) | (abs_value << 1));
    update_flags_rotate(cpu,result,abs_value);
    bus_write(abs_addr,result,bus);



}

void rol_abs_x(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t  abs_value = bus_read(abs_addr,bus);

    uint8_t result = ((cpu->P & CARRY) | (abs_value << 1));
    update_flags_rotate(cpu,result,abs_value);
    bus_write(abs_addr,result,bus);



}

void ror_acc(CPU *cpu, MemoryBus *bus){

    uint8_t result = ((cpu->P & CARRY) | (cpu->A >> 1));
    update_flags_rotate(cpu,result,cpu->A);
    cpu->A = result;

}

void ror_zp(CPU *cpu, MemoryBus *bus){
    uint8_t zp_addr = fetch(cpu,bus);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint8_t result = ((cpu->P & CARRY) | (zp_value >> 1));
    update_flags_rotate(cpu,result,zp_value);
    bus_write(zp_addr,result,bus);

}

void ror_zp_x(CPU *cpu, MemoryBus *bus){

    uint8_t zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->X,ZP_SIZE);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint8_t result = ((cpu->P & CARRY) | (zp_value >> 1));
    update_flags_rotate(cpu,result,zp_value);
    bus_write(zp_addr,result,bus);

}

void ror_abs(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high));
    uint8_t  abs_value = bus_read(abs_addr,bus);

    uint8_t result = ((cpu->P & CARRY) | (abs_value >> 1));
    update_flags_rotate(cpu,result,abs_value);
    bus_write(abs_addr,result,bus);



}

void ror_abs_x(CPU *cpu, MemoryBus *bus){

    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t  abs_value = bus_read(abs_addr,bus);

    uint8_t result = ((cpu->P & CARRY) | (abs_value >> 1));
    update_flags_rotate(cpu,result,abs_value);
    bus_write(abs_addr,result,bus);



}

void update_flags_rotate(CPU *cpu, uint8_t result, uint8_t operand){
    if (operand & 0x80){
        cpu->P |= CARRY;
    } else{
        cpu->P &= ~CARRY;
    }

    if (result == 0){
        cpu->P |= ZERO;
    } else{
        cpu->P &= ~ZERO;
    }

    if (result & 0x80){
        cpu->P |= NEGATIVE;
    } else{
        cpu->P &= ~NEGATIVE;
    }
}

void rti(CPU *cpu, MemoryBus *bus){
    cpu->P = bus_read(STACK_OFFSET(++cpu->S),bus);
    cpu->P |= ONE_FLAG;
    cpu->P &= ~B_FLAG;

    uint8_t low = bus_read(STACK_OFFSET(++cpu->S),bus);
    uint8_t high = bus_read(STACK_OFFSET(++cpu->S),bus);
    cpu->PC = BUILD_FULL_ADDRESS(low,high);
}

void rts(CPU *cpu, MemoryBus *bus){
    uint8_t low = bus_read(STACK_OFFSET(++cpu->S),bus);
    uint8_t high = bus_read(STACK_OFFSET(++cpu->S),bus);
    cpu->PC = BUILD_FULL_ADDRESS(low,high) + 1);
}

void sbc_imm(CPU *cpu, MemoryBus *bus) {
    uint8_t imm_value = fetch(cpu,bus);

    uint16_t result = cpu->A - imm_value - (1 - (cpu->P & CARRY));
    update_flags_sbc(cpu,result,imm_value);

    cpu->A = (uint8_t) result;
}

void sbc_zp(CPU *cpu, MemoryBus *bus) {
    uint8_t zp_addr = fetch(cpu,bus);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint16_t result = cpu->A - zp_value - (1 - (cpu->P & CARRY));
    update_flags_sbc(cpu,result,zp_value);

    cpu->A = (uint8_t) result;
}

void sbc_zp_x(CPU *cpu, MemoryBus *bus) {
    uint8_t zp_addr = WRAP_ADD(fetch(cpu,bus),cpu->X,ZP_SIZE);
    uint8_t zp_value = bus_read(zp_addr,bus);

    uint16_t result = cpu->A - zp_value - (cpu->P & CARRY);
    update_flags_sbc(cpu,result,zp_value);
    cpu->A = (uint8_t) result;
}

void sbc_abs(CPU *cpu, MemoryBus *bus) {
    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high));
    uint8_t  abs_value = bus_read(abs_addr,bus);

    uint16_t result = cpu->A - abs_value - (cpu->P & CARRY);
    update_flags_sbc(cpu,result,abs_value);
    cpu->A = (uint8_t) result;
}

void  sbc_abs_x(CPU *cpu, MemoryBus *bus) {
    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->X;
    uint8_t  abs_value = bus_read(abs_addr,bus);

    uint16_t result = cpu->A - abs_value - (cpu->P & CARRY);
    update_flags_sbc(cpu,result,abs_value);
    cpu->A = (uint8_t) result;
}

void sbc_abs_y(CPU *cpu, MemoryBus *bus) {
    uint8_t low = fetch(cpu,bus);
    uint8_t high = fetch(cpu,bus);

    uint16_t abs_addr = (BUILD_FULL_ADDRESS(low,high)) + cpu->Y;
    uint8_t  abs_value = bus_read(abs_addr,bus);

    uint16_t result = cpu->A - abs_value - (cpu->P & CARRY);
    update_flags_sbc(cpu,result,abs_value);
    cpu->A = (uint8_t) result;
}

void sbc_indr_x(CPU *cpu, MemoryBus *bus) {
    uint8_t zp_addr = fetch(cpu,bus);

    uint8_t low = bus_read(zp_addr,bus);

}

void update_flags_sbc(CPU *cpu, uint16_t result, uint8_t operand) {
    if (result <= 0xFF) {
        cpu->P |= CARRY;
    }else {
        cpu->P &= ~CARRY;
    }

    if (result == 0) {
        cpu->P |= ZERO;
    }else {
        cpu->P &= ~ZERO;
    }

    if (result & 0x80) {
        cpu->P |= NEGATIVE;
    }else {
        cpu->P &= ~NEGATIVE;
    }

    if ((cpu->A ^ result) & (cpu->A ^ operand) & 0x80) {
        cpu->P |= OVERFLOW;
    }else {
        cpu->P &= ~OVERFLOW;
    }
}



