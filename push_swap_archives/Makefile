NAME = push_swap
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g

PS =	ps_cmd.c		ps_cmd_ab.c		main.c		\
		tests.c			tests_utils.c	do_func.c	\
		sample_utils.c	parser.c

PS_NEW	=	do_func.c		free_things.c	global.c	\
			main.c			parser.c		ps_cmd_ab.c	\
			ps_cmd_res.c	ps_cmd.c		states.c	\
			tests.c

PS_SRC = ${addprefix SRCS/, ${PS}}
PS_NEW_SRC = ${addprefix NEW_SRCS/, ${PS_NEW}}
OBJ = ${PS_NEW_SRC:.c=.o}
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
	@${RM} ${OBJ} ${BONUS_OBJ}

fclean: clean
	@${RM} ${NAME} checker
	@make -C libft fclean

re: fclean all

norminette:
	@make -C libft norminette
	@-norminette  | grep -E --color=always "Error" || echo "Norminette: Everything is fine!"

.PHONY: all clean fclean re bonus