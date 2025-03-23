#include "../includes/pe_file.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

DWORD    ft_extract_offs_BRs(FILE *file)
{
    long    NT;
    DWORD   offset;
    DWORD   RVA;

    fseek(file,0x3c, SEEK_SET);
    fread(&NT,sizeof(long), 1 ,file);
    offset = NT + 128;
    fseek(file,offset,SEEK_SET);
    fread(&RVA,sizeof(DWORD), 1 , file);
    return RVA;
}

DWORD   calc_offs_64s(DWORD VA,FILE *file,int size_of_optional_header)
{
    IMAGE_SECTION_HEADER    *sections;
    long                    NT;
    WORD                    numofsect;  
    long                    offset;
    WORD                    index;

    fseek(file, 0x3c, SEEK_SET);
    fread(&NT, sizeof(long), 1, file);
    sections = malloc(sizeof(IMAGE_SECTION_HEADER));
    fseek(file, NT + sizeof(DWORD) + sizeof(WORD), SEEK_SET);
    fread(&numofsect,sizeof(WORD),1,file);
    offset = NT + 24 + size_of_optional_header;
    index = 0;
    while (index < numofsect)
    {
        fseek(file,offset, SEEK_SET);
        fread(sections,40,1,file);
        if((VA >= sections->VirtualAddress) && (VA < (sections->VirtualAddress + sections->Misc.VirtualSize)))
            return (sections->PointerToRawData + (VA
         - sections->VirtualAddress));
        offset = offset + 40;
        index++;
    }
    return 0;
}

void    ft_parse_the_basereloc32(FILE *file, int size_of_optional_header)
{
    IMAGE_BASE_RELOCATION   base;
    IMAGE_BASE_RELOCATION   tmp;
    long                    offset;
    uint32_t                numofentry;
    int                     i;
    DWORD                    offset_entry;
    WORD                    value;

    offset = ft_extract_offs_BRs(file);
    offset = calc_offs_64s(offset,file,size_of_optional_header);
    printf("->BaseReloc (.reloc) : \n\n");
    while(1)
    {
        fseek(file,offset,SEEK_SET);
        fread(&tmp, sizeof(IMAGE_BASE_RELOCATION), 1, file);
        if(tmp.SizeOfBlock == 0x00 || tmp.VirtualAddress == 0x00)
        break;
        printf("   *.VirtualAddress : %X\n", tmp.VirtualAddress);
        printf("    *.SizeOfBlock    : %X\n", tmp.SizeOfBlock);
        numofentry = (tmp.SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
        offset_entry = offset + 2 * sizeof(DWORD);
        printf("    *.NumOfEntries   : %X\n", numofentry);
        i = 0;
        printf("    *.Relocation Block : \n");
        while(i < numofentry)
        {
            fseek(file,offset_entry , SEEK_SET);
            fread(&value, sizeof(WORD) , 1, file);
            printf("        ->Value %X\n ", value);
            printf("           (*)offet_from_RVA :  %X\n\n\n ", value & 0x0FFF );
            i++;
            offset_entry += sizeof(WORD);
        }
        offset += tmp.SizeOfBlock;
    }
}