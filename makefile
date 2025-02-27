CC = gcc
SRCS = dos_header.c machine_type.c pe_file_main.c parse32.c parse64.c header_file.c \
optional_header32.c
OBJ = $(SRCS:.c=.o)
NAME = pe_parser.exe

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)