#ifndef PE_FILE_H
#define PE_FILE_H

#include <stdio.h>
#include "pe_file_content.h"

void    parse_dos_header(FILE *file);
int     file_machine(FILE *file);
void    parse32(FILE    *file);
void    parse64(FILE    *file);
void    parse_header_file(FILE  *file,IMAGE_FILE_HEADER   *hd_fl);
void    parse_optional_header32(FILE  *file,IMAGE_OPTIONAL_HEADER32 *opt);
void    parse_optional_header64(FILE  *file,IMAGE_OPTIONAL_HEADER64 *opt);
void    perse_sections_header32(FILE    *file, int size_of_optional_header);
void    perse_sections_header64(FILE    *file, int size_of_optional_header);
void    ft_parse_import32(FILE  *file,int size_of_optional_header);
void    ft_parse_import64(FILE  *file,int size_of_optional_header);

#endif