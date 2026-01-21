#include "file_parser.h"

const char NES_CONSTANT[NES_CONSTANT_SIZE] = { 'N', 'E', 'S', 0x1A };

Cartridge *parse_file(const char *file_name){
    FILE *file_ptr;
    file_ptr = fopen(file_name,"rb");
    if(file_ptr && check_constant(file_ptr)){

        size_t PRG_size = get_PRG_size(file_ptr);
        size_t CHR_size = get_CHR_size(file_ptr);

        

        uint8_t flag6 = get_byte(file_ptr,FLAG6_LOCATION);
        uint8_t flag7 = get_byte(file_ptr,FLAG7_LOCATION);

        const int trainer = (flag6 & HAS_TRAINER) ? 512 : 0;


        Cartridge *c = build_cartrige(PRG_size,CHR_size,flag6,flag7);
        if(c){
            copy_data(file_ptr,HEADER_SIZE + trainer,PRG_size,c->PRG_data);
            copy_data(file_ptr,(HEADER_SIZE + trainer + PRG_size),CHR_size,c->CHR_data);
        }
        fclose(file_ptr);
        return c;
    }
    fclose(file_ptr);
    return NULL;
}

bool check_constant(FILE *file_ptr){
    char buffer[NES_CONSTANT_SIZE];
    fread(buffer,1,NES_CONSTANT_SIZE,file_ptr);
    return memcmp(buffer,NES_CONSTANT,NES_CONSTANT_SIZE) == 0;

}

size_t  get_PRG_size(FILE *file_ptr){
    fseek(file_ptr,PRG_ROM_LOCATION,SEEK_SET);
    return (size_t) ( getc(file_ptr) * PRG_UNITS);
}

size_t get_CHR_size(FILE *file_ptr){
    fseek(file_ptr,CHR_ROM_LOCATION,SEEK_SET);
    return (size_t) ( getc(file_ptr) * CHR_UNITS);
}

uint8_t get_byte(FILE *file_ptr,const int offset){
    fseek(file_ptr,offset,SEEK_SET);
    return getc(file_ptr);
}

void copy_data(FILE *file_ptr,const int offset,const size_t dest_size,uint8_t *dest){
    fseek(file_ptr,offset,SEEK_SET);
    fread(dest,1,dest_size,file_ptr);
}

