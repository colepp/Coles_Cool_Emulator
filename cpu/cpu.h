#ifndef CPU_H
#define CPU_H

#include "../general/units.h"
#include "../memory/memory_manager.h"


#define CARRY 0x01
#define ZERO 0x02
#define INTURRUPT 0x04
#define DECIMAL 0x08
#define B_FLAG 0x10
#define ONE_FLAG 0x20 // always pushed as one set this on init
#define OVERFLOW 0x40
#define NEGATIVE 0x80


typedef struct {
    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint8_t P;
    uint8_t S;
    uint16_t PC;

} CPU;

typedef void (*Opcode)(CPU *,MemoryBus *);

extern const Opcode opcode_table[];


uint8_t fetch(CPU *cpu,MemoryBus *bus);

Opcode decode(uint8_t b);

void execute(CPU *cpu);


#endif