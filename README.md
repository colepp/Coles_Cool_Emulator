---

# NES Emulator (WIP)

A work-in-progress NES emulator written in C, built from the ground up with correctness and clarity in mind.
The goal is to accurately emulate the 6502 CPU, cartridge loading, and memory bus behavior before moving on to PPU/APU timing.

This project is focused on systems-level accuracy.

---

## Current Progress

### Cartridge / iNES Parsing

* Validates NES magic constant (`NES\x1A`)
* Parses PRG / CHR ROM sizes
* Handles trainer offset
* Builds a `Cartridge` object with:

  * PRG ROM
  * CHR ROM
  * Cartridge RAM
  * Header flags (mapper, mirroring, etc.)

### Memory Bus

* CPU RAM with proper mirroring
* Cartridge RAM support (0x6000–0x7FFF)
* PRG ROM mapping (0x8000–0xFFFF)
* PPU registers stubbed (returns 0 for now)
* Clear separation between address calculation and memory access

### CPU Core (6502)

* CPU registers modeled accurately
* Fetch / decode / execute architecture
* Opcode dispatch table
* Correct flag handling strategy
* ADC implemented with:

  * Immediate
  * Zero Page
  * Zero Page,X
* Proper carry, overflow, zero, and negative flag logic

---

## Design Philosophy

* Correctness first
* Explicit handling of:

  * Addressing modes
  * Mirroring
  * Flag updates
* No hidden behavior in helpers
* CPU communicates with memory only through the bus

---

## What’s Next

* Finish remaining ADC addressing modes
* Implement core load/store ops (LDA/STA/etc.)
* Branching and cycle timing
* PRG bank mirroring (NROM)
* PPU memory and registers
* Instruction timing and sync

---

## References

* [https://www.nesdev.org/wiki/6502_instructions](https://www.nesdev.org/wiki/6502_instructions)

---
