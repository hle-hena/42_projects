NAME = push_swap
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g

PS_SRC = SRCS/push_swap_command_1.c SRCS/main.c

BONUS_SRC =

OBJ = ${PS_SRC:.c=.o}
BONUS_OBJ = ${BONUS_SRC:.c=.o}

.c.o:
	@${CC} ${FLAGS} -c -o $@ $<

${NAME}: ${OBJ}
	@make -C libft
	@${CC} ${FLAGS} ${OBJ} -o push_swap -L libft -lft

bonus: ${BONUS_OBJ}
	@make -C libft
	@${CC} ${FLAGS} ${BONUS_OBJ} -o checker -L libft -lft

all: ${NAME}

clean:
	@make -C libft clean
	@${RM} ${OBJ_1} ${BONUS_OBJ}

fclean: clean
	@${RM} ${NAME} checker
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re bonus