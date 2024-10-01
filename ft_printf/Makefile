NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_printf.c\
		handle_args.c\
		str.c\
		int.c\
		hex.c\
		ft_ternary.c\
		$(wildcard includes/*.c)
OBJ = $(SRC:.c=.o)

EXEC = ft_program

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "Library $(NAME) created."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "Object files cleaned."

fclean: clean
	@rm -f $(NAME) $(EXEC)
	@echo "Library $(NAME) and binary $(EXEC) cleaned."

re: fclean all

binary: $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(EXEC) -g
	@echo "Executable $(EXEC) created. GDB can be used"

.PHONY: all clean fclean re binary
