#ifndef PE_FILE_H
#define PE_FILE_H

#include <stdio.h>
#include "pe_file_content.h"

void    parse_dos_header(FILE *file);
int     file_machine(FILE *file);
void    parse32(FILE    *file);
void    parse64(FILE    *file);
void    parse_header_file(FILE  *file,IMAGE_FILE_HEADER   *hd_fl, IMAGE_DOS_HEADER  *dos);
void    parse_optional_header32(FILE  *file,IMAGE_OPTIONAL_HEADER32 *opt, IMAGE_DOS_HEADER  *dos);
void    parse_optional_header64(FILE  *file,IMAGE_OPTIONAL_HEADER64 *opt, IMAGE_DOS_HEADER  *dos);
#endif