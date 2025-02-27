#include "includes/pe_file.h"
#include <stdlib.h>

// In DOS_HEADER we need only the first element wich is the magic value
// that conftirm that is a PE_FILE and the last element that hold the offset 
// for the NT_HEADER or (file header)

void    parse_dos_header(FILE *file)
{
    IMAGE_DOS_HEADER    *dos;
    DWORD                value;

    dos = malloc(sizeof(IMAGE_DOS_HEADER));
    if(!dos)
        return ;
    dos->e_magic = MAGIC_VALUE;
    fseek(file,0x3C, SEEK_SET); // here we need to mve from the begin of the pe_file to the offset of the elfnew (0x3C)
    fread(&value,sizeof(DWORD),1,file); // here we read from this offset to get the value of the nt_header
    dos->e_lfanew = value;


    printf("->DOS_HEADER :\n");
    printf("    .e_magic   = %X (MZ)\n", dos->e_magic);
    printf("    .e_lfanew  = %X\n\n", dos->e_lfanew);
    printf ("----------------------------------\n\n");

    fseek(file,0,SEEK_SET);
    free(dos);
}