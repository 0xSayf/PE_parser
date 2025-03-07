#include "../includes/pe_file.h"
#include <stdlib.h>

void    perse_sections_header32(FILE    *file, int size_of_optional_header)
{
    IMAGE_SECTION_HEADER    *sections;
    long                    NT;
    WORD                     numofsect;  
    long                    offset;
    WORD                     index;

    fseek(file, 0x3c, SEEK_SET);
    fread(&NT, sizeof(long), 1, file);
    sections = malloc(sizeof(IMAGE_SECTION_HEADER));
    fseek(file, NT + sizeof(DWORD) + sizeof(WORD), SEEK_SET);
    fread(&numofsect,sizeof(WORD),1,file);
    offset = NT + 24 + size_of_optional_header;
    index = 0;
    printf("->Sections_Header :\n\n");
    while (index < numofsect)
    {
        fseek(file,offset, SEEK_SET);
        fread(sections,40,1,file);
        printf("   '*' %s:\n", sections->Name);
        printf("        PhysicalAddress     : 0x%X\n",sections->Misc.PhysicalAddress);
		printf("        VirtualSize         : 0x%X\n", sections->Misc.VirtualSize);
		printf("        VirtualAddress      : 0x%X\n",sections->VirtualAddress);
		printf("        SizeOfRawData       : 0x%X\n", sections->SizeOfRawData);
		printf("        PointerToRawData    : 0x%X\n",sections->PointerToRawData);
		printf("        Characteristics     : 0x%X\n\n", sections->Characteristics);
        offset = offset + 40;
        index++;
    }
    free(sections);
}
