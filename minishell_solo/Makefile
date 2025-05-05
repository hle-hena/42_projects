MAKEFLAGS += --no-print-directory

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g -I./includes
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

DATA_SRC = \
    clean_data.c create_var.c data.c env2env.c \
    ft_getenv_struct.c ft_getenv.c ft_getimp_struct.c ft_getimp.c \
    ft_getloc_struct.c ft_getloc.c init_imp.c is_env.c update_shlvl.c

PROMPT_SRC = \
    $(addprefix prompt/, color.c prompt.c main.c welcome.c random.c) \
	$(addprefix parser/, bt_utils.c build_tree.c expand.c get_ast.c get_cmd_utils.c get_cmd.c get_subshell.c token.c)

MINI_SRC = \
    $(addprefix srcs/data/, $(DATA_SRC)) \
    $(addprefix srcs/prompt/, $(PROMPT_SRC))

OBJ = $(MINI_SRC:.c=.o)

.c.o:
	@printf "\r\033[K\033[34mCompiling: $<\033[0m"
	@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)
	@printf "\r\033[K"

all: $(NAME)

valgrind: $(LIBFT) all
	@valgrind --suppressions=supp.supp --leak-check=full --show-leak-kinds=all --trace-children=yes ./$(NAME)

run: all
	@make clean
	@clear
	@./$(NAME) 4

$(LIBFT):
	@echo
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@echo "\n\033[2K\r\033[94mLinking $(NAME) 🗹\033[0m\n"
	@$(CC) $(OBJ) -o $(NAME) -L $(LIBFT_DIR) -lft -lreadline
	@len=$$(echo -n "$(NAME)" | wc -c); \
	border=$$(printf '=%.0s' $$(seq 1 $$((len + 36)))); \
	echo "\n\033[94m|$$border|\033[0m"; \
	echo "\033[94m|    🎉 $(NAME) Compilation Complete! 🎉    |\033[0m"; \
	echo "\033[94m|$$border|\033[0m\n"

clean:
	@echo -n "\033[34m"
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ)
	@echo "Object files removed\033[0m"

fclean: clean
	@echo -n "\033[34m"
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@$(RM) $(NAME)
	@echo "Binary files and Libft removed\033[0m"

re: fclean all

.PHONY: all clean fclean re
