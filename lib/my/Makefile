##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile 1
##

SRC	=	helpers.c	\
		my_putchar.c	\
		my_put_err.c    \
		my_putstr.c	\
		my_strcat.c	\
		my_strcmp.c	\
		my_strcpy.c	\
		my_strdup.c \
		my_strncat.c	\
		my_strncpy.c	\
		my_str_to_word_array.c	\
		my_str_to_word_array_sep.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

all: $(NAME) cp

$(NAME):	$(OBJ)
	ar rc -o $(NAME) $(OBJ)

cp:
	cp my.h ../../include/my.h

clean:
	rm -f $(OBJ) *~

fclean:	clean
	rm -f $(NAME)
