MAKEFLAGS += --no-print-directory

NAME = fdf
CC = cc
FLAGS = -Wall -Wextra -Werror -O3 -g
RM = rm -f

FRAMEDIR = ./mlx
FRAMEWORK = -Lmlx -lmlx -Imlx -lXext -lX11 -lm -lz

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FDF =	color_utils.c	color.c				draw_utils.c	\
		draw.c			end.c				float.c			\
		init.c			main.c				parser.c		\
		point.c			projection_utils.c	projection.c	\
		rotate.c		movement.c			rotate_utils.c	\
		parser_utils.c	mlx_utils.c			event.c			\
		mlx_hook.c		rotate_quaternion.c	

FDF_SRC = $(addprefix srcs/, $(FDF))

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