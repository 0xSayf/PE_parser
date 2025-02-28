#include "includes/pe_file.h"
#include <stdlib.h>
void    parse64(FILE    *file)
{
    IMAGE_DOS_HEADER    *dos;
    IMAGE_NT_HEADERS64  *nt;
    DWORD               value;

    nt = malloc(sizeof(IMAGE_NT_HEADERS64));
    dos = malloc(sizeof(IMAGE_DOS_HEADER));
    fseek(file, dos->e_lfanew, SEEK_SET);
    fread(&value,sizeof(DWORD), 1, file);
    nt->Signature = value;
    

    printf("->NT_HEADER : \n");
    printf("    .Signature  = %X (%c%c%c%c)\n", nt->Signature, 
        (char)(nt->Signature & 0xFF), 
        (char)((nt->Signature >> 8) & 0xFF), 
        (char)((nt->Signature >> 16) & 0xFF), 
        (char)((nt->Signature >> 24) & 0xFF));
    
    parse_header_file(file,&nt->FileHeader,dos);
    parse_optional_header64(file,&nt->OptionalHeader,dos);
    free(nt);
    free(dos);
}