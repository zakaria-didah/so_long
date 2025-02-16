SRC=get_next_line.c get_next_line_utils.c main_.c utiles.c ft_printf.c validate.c utiles.c utiles1.c

OBJ=$(SRC:%.c=%.o)

NAME=so_long

CC=gcc

libs=libft/libft.a

CFLAGS= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz  #-fsanitize=address -g3

all: make_libs $(NAME)

make_libs:
	$(MAKE) -C libft

$(NAME):  $(OBJ)
	$(CC) $(OBJ) $(libs) $(CFLAGS) -o $(NAME)

%.o: %.c
	$(CC) -std=gnu17 -ggdb3 -Imlx_linux -O3 -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re