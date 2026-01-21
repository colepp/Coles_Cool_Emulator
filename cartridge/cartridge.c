#include "./cartridge.h"


Cartridge *build_cartrige(
    size_t PRG_size,
    size_t CHR_size,
    uint8_t flags6,
    uint8_t flags7){

        Cartridge *new_cartridge = (Cartridge *) malloc(sizeof(Cartridge));
        if(new_cartridge){
            uint8_t *PRG_data = malloc(sizeof(uint8_t) *  PRG_size);
            if(PRG_data){
                uint8_t *CHR_data = malloc(sizeof(uint8_t) *  CHR_size);
                if(CHR_data){
                    uint8_t *cartridge_ram = malloc(sizeof(uint8_t) * CARTRIDGE_RAM_SIZE);
                    if(cartridge_ram){
                        new_cartridge->PRG_size = PRG_size;
                        new_cartridge->CHR_size = CHR_size;
                        new_cartridge->flags6 = flags6;
                        new_cartridge->flags7 = flags7;
                        new_cartridge->CHR_data = CHR_data;
                        new_cartridge->PRG_data = PRG_data;
                        new_cartridge->cartridge_ram = cartridge_ram;
                        return new_cartridge;
                    }
                    free(CHR_data);
                }
            }
            free(PRG_data);
        }
        free(new_cartridge);
        return NULL;
}

void display_information(Cartridge *c){
    printf("PRG size: %u \nCHR size: %u\nFlag6: %x\nFlag7: %x\n",c->PRG_size,c->CHR_data,c->flags6,c->flags7);
}