#include "includes/pe_file.h"

int main (int ac, char **av)
{
    FILE    *file;
    int      machine;
    if(ac != 2)
        return 0;
    file = fopen(av[1], "rb");
    if(!file)
    {
        printf("syntax : pe_parser.exe pe_file(.exe .dll ...)\n");
        return 0;
    }
    machine = file_machine(file);
    if(!machine)
        return 0;
    parse_dos_header(file);
    if(machine == 64)
        parse64(file);
    else if(machine == 32)
        parse32(file);
}