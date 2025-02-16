BIN 	= bin
SRC		= src/main.c src/image_utils.c src/window_utils.c
CFLAGS	= -Wall -Werror -Wextra -g -O3 
LFLAGS	=  -lmlx
UNAME	:= $(shell uname)
NAME	= transparency
RM		= rm -rf
OBJS	= $(SRC:src/%c=$(BIN)/%o)

ifeq ($(UNAME), Darwin)
	CC = gcc
	LFLAGS += -framework OpenGL -framework AppKit
else ifeq ($(UNAME), FreeBSD)
	CC = clang
	LFLAGS += -lbsd -lXext -lX11 -lm
else
	CC	= gcc
	CFLAGS += -D LINUX
	LFLAGS += -lbsd -lXext -lX11 -lm
endif

all: $(NAME)

$(NAME): ${BIN} ${OBJS} 
	${CC} ${OBJS} ${LFLAGS} -o ${NAME} 

$(BIN)/%o: src/%c
	${CC} -c $< ${CFLAGS} -o $@

$(BIN):
	mkdir -p $(BIN)


clean:
	$(RM) $(BIN)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(NAME)

show:
	@printf "UNAME		: $(UNAME)\n"
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "IFLAGS		: $(IFLAGS)\n"
	@printf "SRC		: $(SRC)\n"
	@printf "OBJS		: $(OBJS)\n"


.PHONY: re all clean fclean
