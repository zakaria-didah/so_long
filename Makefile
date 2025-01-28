SRC=get_next_line.c get_next_line_utils.c main.c utiles.c 

NAME=so_long

OBJ=$(SRC:%.c=%.o)

CC=gcc

CFLAGS=-Imlx -framework OpenGL -framework AppKit 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz libftprintf.a minilibx-linux/libmlx_Linux.a -o $(NAME)

%.o: %.c
	$(CC) -Imlx_linux -O3 -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
