#include "includes/pe_file.h"

// before starting parse the PE_FILE we need to know if a 32 or 64 bit 
// but there is difference in structs for the 32 and 64 bits like the OPTINAL_HEADER .....

int file_machine(FILE *file)
{
    WORD    magic;
    WORD    check;
    WORD    elfnew;
    
    fread(&check,sizeof(WORD),1,file);
    
    if(check != MAGIC_VALUE)
    {
        printf("This not a PE_FILE :) \n");
        return 0;
    }

    fseek(file, 0x3c, SEEK_SET); // move to the offset of the NT_HEADER 
    fread(&elfnew,sizeof(LONG),1, file); // read the value (the offset of the NT_HEADER)
    fseek(file, elfnew + 0x14 + sizeof(DWORD), SEEK_SET); // move to the magic value in the OPTIONAL_HEADER
    fread(&magic,sizeof(WORD),1, file); // read the value of the magic (64-bit = 20B / 32-bit = 10B)
    if(magic == 0x20B)
        return 64;
    else if(magic == 0x10B)
        return 32;
    else
    {
        printf("unknown type");
       return 0;
    }
    return 0;
}