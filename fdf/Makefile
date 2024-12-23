MAKEFLAGS += --no-print-directory

NAME = fdf
CC = cc
FLAGS = -Wall -Wextra -Werror -o3 -g
RM = rm -f

FRAMEDIR = ./mlx
FRAMEWORK = -Lmlx -lmlx -Imlx -lXext -lX11 -lm -lz

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FDF =	draw_utils.c	draw.c			end.c		\
		init.c			main.c			parser.c	\
		rotate.c		projection.c	color.c		\
		float.c

NEW_FDF =	draw_utils.c	draw.c	end.c		\
			init.c			main.c	parser.c	\
			rotate.c	

FDF_SRC = $(addprefix srcs/, $(FDF))
# FDF_SRC = $(addprefix new_srcs/, $(NEW_FDF))

OBJ = $(FDF_SRC:.c=.o)

.c.o: 
	@$(CC) $(FLAGS) -Imlx -c $< -o $(<:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) $(FRAMEWORK) -o $(NAME) -L $(LIBFT_DIR) -lft
	@echo "$(NAME) compiled successfully!"

clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ) $(BONUS_OBJ)
	@echo "Object files removed"

fclean: clean
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@$(RM) $(NAME) checker
	@echo "Binary files and Libft removed"

re: fclean all

norminette:
	@make -C $(LIBFT_DIR) norminette
	@-norminette srcs | grep -E --color=always "Error" || echo "Norminette: Everything is fine!"

.PHONY: all clean fclean re bonus norminette