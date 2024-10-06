NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC = src/ft_printf.c\
		src/handle_args.c\
		src/str.c\
		src/digits.c\
		src/ft_ternary.c\
		$(wildcard includes/*.c)
OBJ = $(SRC:.c=.o)

EXEC = ft_program

bonus: ${NAME}

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

test: ${NAME}
	@$(CC) $(CFLAGS) full_test.c $(NAME) -o ${EXEC}

.PHONY: all clean fclean re binary
