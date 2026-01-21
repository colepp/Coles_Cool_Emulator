#ifndef FILE_PARSER_H
#define FILE_PARSER_H
#include "../cartridge/cartridge.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Most Information on the .nes file can be found at https://www.nesdev.org/wiki/INES



#define NES_CONSTANT_LOCATION 0

#define PRG_ROM_LOCATION 4

#define CHR_ROM_LOCATION 5

#define FLAG6_LOCATION 6

#define FLAG7_LOCATION 7

#define HAS_TRAINER 0x02


extern const char NES_CONSTANT[];

Cartridge *parse_file(const char *file_name);

bool check_constant(FILE *file_ptr);

size_t get_PRG_size(FILE *file_ptr);
size_t get_CHR_size(FILE *file_ptr);

uint8_t get_byte(FILE *file_ptr,const int offset);

void copy_data(FILE *file_ptr,const int offset,const size_t dest_size,uint8_t *dest);


#endif