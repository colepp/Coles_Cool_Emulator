#ifndef OPCODES_H
#define OPCODE_H

#include "cpu.h"

#define ADC_IMM 0x69
#define ADC_ZP 0x65
#define ADC_ZP_X 0x75
#define ADC_ABS 0x6D
#define ADC_ABS_X 0x7D
#define ADC_ABS_Y 0x79
#define ADC_INDR_X 0x61
#define ADC_INDR_Y 0x71

#define AND_IMM 0x29
#define AND_ZP 0x25
#define AND_ZP_X 0x35
#define AND_ABS 0x2D
#define AND_ABS_X 0x3D
#define AND_ABS_Y 0x39
#define AND_INDR_X 0x21
#define AND_INDR_Y 0x31

#define ASL_ACC 0x0A
#define ASL_ZP 0x06
#define ASL_ZP_X 0x16
#define ASL_ABS 0x0E
#define ASL_ABS_X 0x1E

#define BCC 0x90
#define BCS 0xB0
#define BEQ 0xF0

#define BIT_ZP 0x24
#define BIT_ABS 0x2C

#define BMI 0x30
#define BNE 0xD0
#define BPL 0x10

#define BRK 0x00

#define BVC 0x50
#define BVS 0x70

#define CLC 0x18
#define CLD 0xD8
#define CLI 0x58
#define CLV 0xB8

#define CMP_IMM 0xC9
#define CMP_ZP 0xC9
#define CMP_ZP_X 0xC9
#define CMP_ABS 0xCD
#define CMP_ABS_X 0xDD
#define CMP_ABS_Y 0xD9
#define CMP_INDR_X 0xC1
#define CMP_INDR_Y 0xD1

#define CPX_IMM 0xE0
#define CPX_ZP 0xE4
#define CPX_ABS 0xEC

#define CPY_IMM 0xC0
#define CPY_ZP 0xC4
#define CPY_ABS 0xCC

#define DEC_ZP 0xC6
#define DEC_ZP_X 0xD6
#define DEC_ABS 0xCE
#define DEC_ABS_X 0xDE

#define DEX 0xCA
#define DEY 0x88



#define BUILD_FULL_ADDRESS(low,high) (((high) << 8) | (low))
#define WRAP_ADD(x,y,wrapper) (((x) + (y)) % (wrapper))




void adc_imm(CPU *cpu, MemoryBus *bus);
void adc_zp(CPU *cpu, MemoryBus *bus);
void adc_zp_x(CPU *cpu, MemoryBus *bus);
void adc_abs(CPU *cpu, MemoryBus *bus);
void adc_abs_x(CPU *cpu, MemoryBus *bus);
void adc_abs_y(CPU *cpu, MemoryBus *bus);
void adc_indr_x(CPU *cpu, MemoryBus *bus);
void adc_indr_y(CPU *cpu, MemoryBus *bus);
void update_flags_adc(CPU *cpu,uint16_t result,uint8_t operand);

void and_imm(CPU *cpu, MemoryBus *bus);
void and_zp(CPU *cpu, MemoryBus *bus);
void and_zp_x(CPU *cpu, MemoryBus *bus);
void and_abs(CPU *cpu, MemoryBus *bus);
void and_abs_x(CPU *cpu, MemoryBus *bus);
void and_abs_y(CPU *cpu, MemoryBus *bus);
void and_indr_x(CPU *cpu, MemoryBus *bus);
void and_indr_y(CPU *cpu, MemoryBus *bus);
void update_flags_and(CPU *cpu,uint8_t result);

void asl_acc(CPU *cpu,MemoryBus *bus);
void asl_zp(CPU *cpu,MemoryBus *bus);
void asl_zp_x(CPU *cpu,MemoryBus *bus);
void asl_abs(CPU *cpu,MemoryBus *bus);
void asl_abs_x(CPU *cpu,MemoryBus *bus);
void update_flags_asl(CPU *cpu,uint8_t result,uint8_t operand);

void bcc(CPU *cpu,MemoryBus *bus);
void bcs(CPU *cpu,MemoryBus *bus);
void beq(CPU *cpu,MemoryBus *bus);

void bit_zp(CPU *cpu,MemoryBus *bus);
void bit_abs(CPU *cpu,MemoryBus *bus);

void bmi(CPU *cpu,MemoryBus *bus);
void bne(CPU *cpu,MemoryBus *bus);
void bpl(CPU *cpu,MemoryBus *bus);

void brk(CPU *cpu,MemoryBus *bus);

void bvc(CPU *cpu,MemoryBus *bus);
void bvs(CPU *cpu,MemoryBus *bus);

void clc(CPU *cpu,MemoryBus *bus);
void cld(CPU *cpu,MemoryBus *bus);
void cli(CPU *cpu,MemoryBus *bus);
void clv(CPU *cpu,MemoryBus *bus);


#endif
