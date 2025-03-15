#include "../includes/pe_file.h"
#include <stdlib.h>

DWORD   ft_extract_the_RVA(FILE *file)
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

DWORD   calc_off(DWORD VA,FILE *file,int size_of_optional_header)
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

DWORD   ft_calc_the_offset_of_import(FILE *file,int   size_of_optional_header)
{
    IMAGE_SECTION_HEADER    *sections;
    long                    NT;
    WORD                    numofsect;  
    long                    offset;
    WORD                    index;
    DWORD                   RVA;

    fseek(file, 0x3c, SEEK_SET);
    fread(&NT, sizeof(long), 1, file);
    sections = malloc(sizeof(IMAGE_SECTION_HEADER));
    fseek(file, NT + sizeof(DWORD) + sizeof(WORD), SEEK_SET);
    fread(&numofsect,sizeof(WORD),1,file);
    offset = NT + 24 + size_of_optional_header;
    index = 0;
    RVA = ft_extract_the_RVA(file);
    while (index < numofsect)
    {
        fseek(file,offset, SEEK_SET);
        fread(sections,40,1,file);
        if((RVA >= sections->VirtualAddress) && (RVA < (sections->VirtualAddress + sections->Misc.VirtualSize)))
            return (sections->PointerToRawData + (RVA - sections->VirtualAddress));
        offset = offset + 40;
        index++;
    }
    return 0;
}

void    ft_parse_import32(FILE  *file,int size_of_optional_header)
{
    IMAGE_IMPORT_DESCRIPTOR tmp;
    IMAGE_IMPORT_BY_NAME    *ILT;
    char                    dll_name[256];
    DWORD                   hhh;
    IMAGE_THUNK_DATA        *IDT;
    DWORD                   offset;

    offset = ft_calc_the_offset_of_import(file,size_of_optional_header);
    while (1)
    {
        fseek(file,offset,SEEK_SET);
        fread(&tmp,sizeof(IMAGE_IMPORT_DESCRIPTOR), 1 , file);
        if(!tmp.Name)
            break;
        offset = offset + sizeof(tmp);
        hhh = calc_off(tmp.Name,file,size_of_optional_header);
        fseek(file,hhh,SEEK_SET);
        fread(dll_name,sizeof(char), sizeof(dll_name) , file);
        printf("%s\n", dll_name);
    }
}