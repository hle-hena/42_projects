MAKEFLAGS += --no-print-directory

NAME = push_swap
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g

PUSH_SWAP =	commands_1.c	commands_2.c	do_funcs.c	\
			do_push.c		ends.c			global.c	\
			main.c			parser.c		struct_func.c

CHECKER =	commands_1.c	commands_2.c	do_funcs.c	\
			ends.c			global.c		main.c		\
			parser.c

PUSH_SWAP_SRC = ${addprefix srcs/solver/, ${PUSH_SWAP}}
CHECKER_SRC = ${addprefix srcs/checker/, ${CHECKER}}
OBJ = ${PUSH_SWAP_SRC:.c=.o}
BONUS_OBJ = ${CHECKER_SRC:.c=.o}

LIBFT_DIR = libft
LIBFT = ${LIBFT_DIR}/libft.a

.c.o:
	@${CC} ${FLAGS} -c -o $@ $<

${NAME}: ${LIBFT} ${OBJ}
	@${CC} ${FLAGS} ${OBJ} -o ${NAME} -L ${LIBFT_DIR} -lft
	@echo "${NAME} compiled successfully!"
	
bonus: checker

checker: ${LIBFT} ${BONUS_OBJ}
	@${CC} ${FLAGS} ${BONUS_OBJ} -o checker -L ${LIBFT_DIR} -lft
	@echo "checker compiled successfully!"

${LIBFT}:
	@make -C ${LIBFT_DIR}

all: ${NAME}

clean:
	@make -C ${LIBFT_DIR} clean
	@${RM} ${OBJ} ${BONUS_OBJ}
	@echo "Object files removed"

fclean: clean
	@make -C ${LIBFT_DIR} fclean > /dev/null
	@${RM} ${NAME} checker
	@echo "Binary files and Libft removed"

re: fclean all

norminette:
	@make -C ${LIBFT_DIR} norminette
	@-norminette  | grep -E --color=always "Error" || echo "Norminette: Everything is fine!"

.PHONY: all clean fclean re bonus norminette