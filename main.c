#include "./parser/file_parser.h"

int main(int argc,char *argv[]){
    if(argc > 1){
        printf("parsing\n");
        char *file_name = argv[1];
        Cartridge *c = parse_file(file_name);
        if(c) printf("Cartridge Successfully Created\n");
        display_information(c);

    }
}