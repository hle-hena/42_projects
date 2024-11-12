NAME = libftprintf.a
EXEC = printf.out

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = src/ft_printf.c\
		src/handle_args.c\
		src/str.c\
		src/digits.c\
		src/ft_ternary.c\
		includes/ft_atoi.c\
		includes/ft_putchar_fd.c\
		includes/ft_putstr_fd.c\
		includes/ft_putnbr_fd.c\
		includes/ft_strchr.c\
		includes/ft_strlen.c

OBJ = $(SRC:.c=.o)

bonus: ${NAME}

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "Library $(NAME) created."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

binary: $(SRC)
	@$(CC) $(SRC) -o $(EXEC) -g
	@echo "Executable $(EXEC) created. GDB can be used"

test: ${NAME}
	@$(CC) $(CFLAGS) full_test.c $(NAME) -o ${EXEC}

norminette:
	@-norminette src/ includes | grep -E --color=always "Error" || echo "Norminette: Everything is fine!"

clean:
	@rm -f $(OBJ)
	@echo "Object files cleaned."

fclean: clean
	@rm -f $(NAME) $(EXEC)
	@echo "Library $(NAME) and binary $(EXEC) cleaned."

re: fclean all

.PHONY: all clean fclean re binary
