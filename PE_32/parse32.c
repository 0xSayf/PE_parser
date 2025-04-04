#include "../includes/pe_file.h"
#include <stdlib.h>

void    parse32(FILE    *file)
{
    IMAGE_NT_HEADERS32  *nt;
    DWORD               value;
    long                NT;

    nt = malloc(sizeof(IMAGE_NT_HEADERS32));
    fseek(file,0x3c, SEEK_SET);
    fread(&NT,sizeof(long),1,file);
    fseek(file, NT, SEEK_SET);
    fread(&value,sizeof(DWORD), 1, file);
    nt->Signature = value;
    

    printf("->NT_HEADER : \n");
    printf("    .Signature  = %X (%c%c%c%c)\n", nt->Signature, 
        (char)(nt->Signature & 0xFF), 
        (char)((nt->Signature >> 8) & 0xFF), 
        (char)((nt->Signature >> 16) & 0xFF), 
        (char)((nt->Signature >> 24) & 0xFF));
    
    parse_header_file(file,&nt->FileHeader);
    parse_optional_header32(file,&nt->OptionalHeader);
    perse_sections_header32(file, sizeof(nt->OptionalHeader));
    ft_parse_import32(file,sizeof(nt->OptionalHeader));
    ft_parse_the_basereloc32(file, sizeof(IMAGE_OPTIONAL_HEADER32));
    free(nt);
}