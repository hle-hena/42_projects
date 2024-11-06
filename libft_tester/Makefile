SRC = test.c

CHILD = -C libft/

OBJ = ${SRC:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = program

all: ${NAME}

${NAME}: ${OBJ}
	@${MAKE} ${CHILD}
	@${CC} ${CFLAGS} ${OBJ} -L libft -lft -o ${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -c -o $@ $<

norminette:
	@${MAKE} norminette ${CHILD}

clean:
	@${MAKE} clean ${CHILD}
	@rm -f ${OBJ} ${OBJ_BONUS}

fclean: clean
	@${MAKE} fclean ${CHILD}
	@rm -f ${NAME}

re: fclean all