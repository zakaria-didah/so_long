SRC=ft_printf.c \
	get_next_line.c  get_next_line_utils.c  main.c \
	mlx_img_things.c  movemenet.c  utiles.c  utiles1.c \
	utiles2.c  validate.c utiles3.c

OBJ=$(SRC:%.c=%.o)

NAME=so_long

CC=gcc

libs=libft/libft.a

CFLAGS=  -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 

all: make_libs $(NAME)

make_libs:
	$(MAKE) bonus -C libft

$(NAME):  $(OBJ)
	$(CC) $(OBJ) $(libs) $(CFLAGS) -o $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx_linux -O3 -g3 -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re