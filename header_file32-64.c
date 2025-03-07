#include "includes/pe_file.h"
#include <stdlib.h>

void    parse_header_file(FILE  *file,IMAGE_FILE_HEADER   *hd_fl)
{
    WORD                 value;
    LONG                 offset;
    long                 NT;

    fseek(file,0x3c, SEEK_SET);
    fread(&NT,sizeof(long),1,file);
    offset = sizeof(DWORD) + NT;
    hd_fl = malloc(sizeof(IMAGE_FILE_HEADER));
    fseek(file,offset, SEEK_SET);
    fread(hd_fl,sizeof(IMAGE_FILE_HEADER),1,file);
    
    printf("    .FileHeader :\n");
    printf("        .Machine               = %X\n",hd_fl->Machine);
    printf("        .NumberOfSections      = %X\n", hd_fl->NumberOfSections);
    printf("        .TimeDateStamp         = %X\n",hd_fl->TimeDateStamp);
    printf("        .PointerToSymbolTable  = %X\n",hd_fl->PointerToSymbolTable);
    printf("        .NumberOfSymbols       = %X\n",hd_fl->NumberOfSymbols);
    printf("        .SizeOfOptionalHeader  = %X\n",hd_fl->SizeOfOptionalHeader);
    printf("        .Characteristics       = %X\n",hd_fl->Characteristics);
    
    free(hd_fl);
}