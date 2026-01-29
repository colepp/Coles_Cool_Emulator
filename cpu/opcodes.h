#ifndef OPCODES_H
#define OPCODES_H

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

#define EOR_IMM 0x49
#define EOR_ZP 0x45
#define EOR_ZP_X 0x55
#define EOR_ABS 0x4D
#define EOR_ABS_X 0x5D
#define EOR_ABS_Y 0x59
#define EOR_INDR_X 0x41
#define EOR_INDR_Y 0x51

#define INC_ZP 0xE6
#define INC_ZP_X 0xF6
#define INC_ABS 0xEE
#define INC_ABS_X 0xFE

#define INX 0xE8
#define INY 0xC8

#define JMP_ABS 0x4C
#define JMP_INDR 0x6C

#define JSR 0x20

#define LDA_IMM 0xA9
#define LDA_ZP 0xA5
#define LDA_ZP_X 0xB5
#define LDA_ABS 0xAD
#define LDA_ABS_X 0xBD
#define LDA_ABS_Y 0xB9
#define LDA_INDR_X 0xA1
#define LDA_INDR_Y 0xB1

#define LDX_IMM 0xA2
#define LDX_ZP 0xA6
#define LDX_ZP_Y 0xB6
#define LDX_ABS 0xAE
#define LDX_ABS_Y 0xBE

#define LDY_IMM 0xA0
#define LDY_ZP 0xA4
#define LDY_ZP_X 0xB4
#define LDY_ABS 0xAC
#define LDY_ABS_X 0xBC

#define LSR_ACC 0x4A
#define LSR_ZP 0x46
#define LSR_ZP_X 0x56
#define LSR_ABS 0x4E
#define LSR_ABS_X 0x5E

#define NOP 0xEA



#define BUILD_FULL_ADDRESS(low,high) (((high) << 8) | (low))
#define WRAP_ADD(x,y,wrapper) (((x) + (y)) % (wrapper))
#define STACK_OFFSET(sp) ((sp) + 0x0100)




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
void update_flags_bit(CPU *cpu, uint8_t result, uint8_t memory);

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

void cmp_imm(CPU *cpu, MemoryBus *bus);
void cmp_zp(CPU *cpu, MemoryBus *bus);
void cmp_zp_x(CPU *cpu, MemoryBus *bus);
void cmp_abs(CPU *cpu, MemoryBus *bus);
void cmp_abs_x(CPU *cpu, MemoryBus *bus);
void cmp_abs_y(CPU *cpu, MemoryBus *bus);
void cmp_indr_x(CPU *cpu, MemoryBus *bus);
void cmp_indr_y(CPU *cpu, MemoryBus *bus);

void cpx_imm(CPU *cpu, MemoryBus *bus);
void cpx_zp(CPU *cpu, MemoryBus *bus);
void cpx_abs(CPU *cpu, MemoryBus *bus);

void cpy_imm(CPU *cpu, MemoryBus *bus);
void cpy_zp(CPU *cpu, MemoryBus *bus);
void cpy_abs(CPU *cpu, MemoryBus *bus);

void update_flags_cmp(CPU *cpu,uint8_t result,uint8_t memory);

void dec_zp(CPU *cpu, MemoryBus *bus);
void dec_zp_x(CPU *cpu, MemoryBus *bus);
void dec_abs(CPU *cpu, MemoryBus *bus);
void dec_abs_x(CPU *cpu, MemoryBus *bus);

void dex(CPU *cpu, MemoryBus *bus);
void dey(CPU *cpu, MemoryBus *bus);

void update_flags_decrement(CPU *cpu,uint8_t result);

void eor_imm(CPU *cpu, MemoryBus *bus);
void eor_zp(CPU *cpu, MemoryBus *bus);
void eor_zp_x(CPU *cpu, MemoryBus *bus);
void eor_abs(CPU *cpu, MemoryBus *bus);
void eor_abs_x(CPU *cpu, MemoryBus *bus);
void eor_abs_y(CPU *cpu, MemoryBus *bus);
void eor_indr_x(CPU *cpu, MemoryBus *bus);
void eor_indr_y(CPU *cpu, MemoryBus *bus);

void update_flags_eor(CPU *cpu,uint8_t  result);


void inc_zp(CPU *cpu, MemoryBus *bus);
void inc_zp_x(CPU *cpu, MemoryBus *bus);
void inc_abs(CPU *cpu, MemoryBus *bus);
void inc_abs_x(CPU *cpu, MemoryBus *bus);

void inx(CPU *cpu, MemoryBus *bus);
void iny(CPU *cpu, MemoryBus *bus);

void update_flags_increment(CPU *cpu, uint8_t result);

void jmp_abs(CPU *cpu, MemoryBus *bus);
void jmp_indr(CPU *cpu, MemoryBus *bus);

void jsr(CPU *cpu, MemoryBus *bus);

void lda_imm(CPU *cpu, MemoryBus *bus);
void lda_zp(CPU *cpu, MemoryBus *bus);
void lda_zp_x(CPU *cpu, MemoryBus *bus);
void lda_abs(CPU *cpu, MemoryBus *bus);
void lda_abs_x(CPU *cpu, MemoryBus *bus);
void lda_abs_y(CPU *cpu, MemoryBus *bus);
void lda_indr_x(CPU *cpu, MemoryBus *bus);
void lda_indr_y(CPU *cpu, MemoryBus *bus);

void ldx_imm(CPU *cpu, MemoryBus *bus);
void ldx_zp(CPU *cpu, MemoryBus *bus);
void ldx_zp_y(CPU *cpu, MemoryBus *bus);
void ldx_abs(CPU *cpu, MemoryBus *bus);
void ldx_abs_y(CPU *cpu, MemoryBus *bus);

void ldy_imm(CPU *cpu, MemoryBus *bus);
void ldy_zp(CPU *cpu, MemoryBus *bus);
void ldy_zp_x(CPU *cpu, MemoryBus *bus);
void ldy_abs(CPU *cpu, MemoryBus *bus);
void ldy_abs_x(CPU *cpu, MemoryBus *bus);

void update_flags_load(CPU *cpu, uint8_t result);

void lsr_acc(CPU *cpu, MemoryBus *bus);
void lsr_zp(CPU *cpu, MemoryBus *bus);
void lsr_zp_x(CPU *cpu, MemoryBus *bus);
void lsr_abs(CPU *cpu, MemoryBus *bus);
void lsr_abs_x(CPU *cpu, MemoryBus *bus);

void update_flags_lsr(CPU *cpu, uint8_t result,uint8_t operand);

void nop(CPU *cpu,MemoryBus *bus);



#endif
