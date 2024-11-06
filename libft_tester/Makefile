SRC = ft_strlen_test.c ft_is_test.c

CHILD = -C libft/

OBJ = ${SRC:.c=.o}

MAKEFLAGS += --no-print-directory

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = program

all: ${NAME}

${NAME}: ${OBJ}
	@${MAKE} ${CHILD}
	@${CC} ${CFLAGS} ${OBJ} -L libft -lft -o ${NAME}
	./${NAME}
	@${MAKE} fclean

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