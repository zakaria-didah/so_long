SRC=get_next_line.c get_next_line_utils.c main.c utiles.c libmlx.dylib ft_printf/libftprintf.a

NAME=so_long

CC=gcc

CFLAGS=-Imlx -framework OpenGL -framework AppKit 

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re

