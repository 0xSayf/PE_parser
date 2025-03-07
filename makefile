CC = gcc
SRCS = dos_header32-64.c machine_type32-64.c pe_file_main.c PE_32/parse32.c PE_64/parse64.c header_file32-64.c \
PE_32/optional_header32.c PE_64/optional_header64.c PE_32/sections32.c PE_64/sections64.c
OBJ = $(SRCS:.c=.o)
NAME = pe_parser.exe

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)