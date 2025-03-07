#include "../includes/pe_file.h"
#include <stdlib.h>

void    parse_optional_header64(FILE  *file,IMAGE_OPTIONAL_HEADER64 *opt)
{
    LONG    offset;
    DWORD   value;
    long    NT;
    
    fseek(file,0x3c, SEEK_SET);
    fread(&NT,sizeof(long),1,file);
    offset = NT + 24;
    opt = malloc(sizeof(IMAGE_OPTIONAL_HEADER64));
    fseek(file, offset, SEEK_SET);
    fread(opt,sizeof(IMAGE_OPTIONAL_HEADER64), 1,file);

    printf("    .Optional_header :\n");
    printf("        .Magic                      = %X\n",opt->Magic);
    printf("        .MajorLinkerVersion         = %X\n",opt->MajorLinkerVersion);
    printf("        .MinorLinkerVersion         = %X\n",opt->MinorLinkerVersion);
    printf("        .SizeOfCode                 = %X\n",opt->SizeOfCode);
    printf("        .SizeOfInitializedData      = %X\n",opt->SizeOfInitializedData);
    printf("        .SizeOfUninitializedData    = %X\n",opt->SizeOfUninitializedData);
    printf("        .AddressOfEntryPoint        = %X\n",opt->AddressOfEntryPoint);
    printf("        .BaseOfCode                 = %X\n",opt->BaseOfCode);
    printf("        .ImageBase                  = %X\n",opt->ImageBase);
    printf("        .SectionAlignment           = %X\n",opt->SectionAlignment);
    printf("        .FileAlignment              = %X\n",opt->FileAlignment);
    printf("        .MajorOperatingSystemVersion= %X\n",opt->MajorOperatingSystemVersion);
    printf("        .MinorOperatingSystemVersion= %X\n",opt->MinorOperatingSystemVersion);
    printf("        .MajorImageVersion          = %X\n",opt->MajorImageVersion);
    printf("        .MajorSubsystemVersion      = %X\n",opt->MajorSubsystemVersion);
    printf("        .MinorSubsystemVersion      = %X\n",opt->MinorSubsystemVersion);
    printf("        .Win32VersionValue          = %X\n",opt->Win32VersionValue);
    printf("        .SizeOfImage                = %X\n",opt->SizeOfImage);
    printf("        .SizeOfHeaders              = %X\n",opt->SizeOfHeaders);
    printf("        .CheckSum                   = %X\n",opt->CheckSum);
    printf("        .Subsystem                  = %X\n",opt->Subsystem);
    printf("        .DllCharacteristics         = %X\n",opt->DllCharacteristics);
    printf("        .SizeOfStackReserve         = %X\n",opt->SizeOfStackReserve);
    printf("        .SizeOfStackCommit          = %X\n",opt->SizeOfStackCommit);
    printf("        .SizeOfHeapReserve          = %X\n",opt->SizeOfHeapReserve);
    printf("        .LoaderFlags                = %X\n",opt->LoaderFlags);
    printf("        .NumberOfRvaAndSizes        = %X\n\n",opt->NumberOfRvaAndSizes);
    printf ("----------------------------------\n\n");
}
