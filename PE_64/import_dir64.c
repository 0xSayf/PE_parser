#include "../includes/pe_file.h"
#include <stdlib.h>
#include <string.h>

DWORD   ft_extract_the_RVA_64(FILE *file)
{
    IMAGE_OPTIONAL_HEADER64 nt;
    long    NT;
    DWORD   offset;
    DWORD   RVA;

    fseek(file,0x3c, SEEK_SET);
    fread(&NT,sizeof(long), 1 ,file);
    offset = NT + 24;
    fseek(file,offset,SEEK_SET);
    fread(&nt,sizeof(IMAGE_OPTIONAL_HEADER64), 1 ,file);
    RVA = nt.DataDirectory[1].VirtualAddress;
    return RVA;
}

DWORD   calc_off_64(DWORD VA,FILE *file,int size_of_optional_header)
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

DWORD   ft_calc_the_offset_of_import_64(FILE *file,int   size_of_optional_header)
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
    RVA = ft_extract_the_RVA_64(file);
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

void    ft_ILT_parse_64(FILE   *file, int size_of_optional_header , DWORD RVA_ILT)
{
    IMAGE_IMPORT_BY_NAME    ilt;
    ILT_CUST_64              entry;
    BYTE                    flag;
    WORD                    ordinal;
    DWORD                   offset_ILT;
    DWORD                   offset;

    while (1)
    {
        offset = calc_off_64(RVA_ILT,file,size_of_optional_header);
        fseek(file , offset , SEEK_SET);
        fread(&entry, sizeof(ILT_CUST_64), 1 , file);
        ordinal = 0x00;
        offset_ILT = 0x00;
        flag = entry.myaw.flag;
        if(flag == 0x01)
            ordinal = entry.myaw.ordinal;
        else if(flag == 0x0)
            offset_ILT = entry.myaw.RVA_by_NAME;
        if(flag == 0x0 && offset_ILT == 0x00 && ordinal == 0x00)
            break;
        if(flag == 0x0)
        {
            offset_ILT = calc_off_64(offset_ILT, file, size_of_optional_header);
            fseek(file,offset_ILT,SEEK_SET);
            fread(&ilt,sizeof(IMAGE_IMPORT_BY_NAME),1,file);
            printf("      . Entry(funtion) :\n");
            printf("            Function : %s\n", ilt.Name);
            printf("            Hint : %X\n\n", ilt.Hint);
        }
        else if(flag == 0x01)
            printf ("Called by the ordinal : %d \n", ordinal);
        RVA_ILT += sizeof(QWORD);
    }        
}

void    ft_parse_import64(FILE  *file,int size_of_optional_header)
{
    IMAGE_IMPORT_DESCRIPTOR tmp;
    char                    dll_name[256];
    DWORD                   hhh;
    DWORD                   offset;

    printf("->ImportDirectory : \n\n");
    offset = ft_calc_the_offset_of_import_64(file,size_of_optional_header);
   
    while (1)
    {
        fseek(file,offset,SEEK_SET);
        fread(&tmp,sizeof(IMAGE_IMPORT_DESCRIPTOR), 1 , file);
        if(!tmp.Name)
            break;
        hhh = calc_off_64(tmp.Name,file,size_of_optional_header);
        fseek(file,hhh,SEEK_SET);
        fread(dll_name,sizeof(char), sizeof(dll_name) , file);
        printf("    *. %s\n", dll_name);
        ft_ILT_parse_64(file,size_of_optional_header,tmp.ILT.OriginalFirstThunk);
        offset += sizeof(tmp);
    }
}