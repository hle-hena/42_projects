LST =		ft_lstadd_back.c	ft_lstclear.c		ft_lstiter.c		\
			ft_lstmap.c			ft_lstsize.c		ft_lstadd_front.c	\
			ft_lstdelone.c		ft_lstlast.c		ft_lstnew.c			\
			ft_lstsorted.c

IS =		ft_isalnum.c		ft_isalpha.c		ft_isascii.c		\
			ft_isdigit.c		ft_isprint.c		ft_isspace.c		\
			ft_toupper.c		ft_tolower.c

STR =		ft_split.c			ft_strchr.c			ft_strdup.c			\
			ft_striteri.c		ft_strjoin.c		ft_strlcat.c		\
			ft_strlcpy.c		ft_strlen.c			ft_strmapi.c		\
			ft_strncmp.c		ft_strnstr.c		ft_strrchr.c		\
			ft_strtrim.c		ft_substr.c

MEM =		ft_bzero.c			ft_calloc.c			ft_memccpy.c		\
			ft_memchr.c			ft_memcmp.c			ft_memcpy.c			\
			ft_memmove.c		ft_memset.c			ft_realloc.c	

PRINT = 	ft_putchar_fd.c		ft_putendl_fd.c		ft_putnbr_fd.c		\
			ft_putstr_fd.c

MATH =		ft_atoi.c			ft_itoa.c			ft_power.c

F =			ft_ternary.c

STR_SRC = $(addprefix str/, $(STR))
LST_SRC = $(addprefix lst/, $(LST))
IS_SRC = $(addprefix is/, $(IS))
MEM_SRC = $(addprefix mem/, $(MEM))
PRINT_SRC = $(addprefix print/, $(PRINT))
MATH_SRC = $(addprefix math/, $(MATH))
F_SRC = $(addprefix freedom/, $(F))

SRC = $(LST_SRC) $(IS_SRC) $(STR_SRC) $(MEM_SRC) $(PRINT_SRC) $(MATH_SRC) $(F_SRC)
OBJ = ${SRC:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

all: ${NAME}

${NAME}: ${OBJ}
	@ar rcs ${NAME} ${OBJ}
	@echo "Library ready to be used"

%.o: %.c
	@${CC} ${CFLAGS} -c -o $@ $<

norminette:
	@-norminette | grep -E --color=always "Error" || echo "Norminette in libft: Everything is fine!"

clean:
	@rm -f ${OBJ} ${OBJ_BONUS}
	@echo "Files removed"

fclean: clean
	@rm -f ${NAME}
	@echo "Libft removed"

re: fclean all