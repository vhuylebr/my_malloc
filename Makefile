##
## EPITECH PROJECT, 2018
## make
## File description:
## make
##

CC	=	gcc

RM	=	rm -f

NAME	=	libmy_malloc.so

CFLAGS	=	-Wall -Wextra -fPIC -Iinclude

SRC	=	src/show_alloc_mem.c \
		src/handle.c \
		src/free.c \
		src/calloc.c \
		src/malloc.c \
		src/first_block.c \
		src/realloc.c

OBJ	=	$(SRC:.c=.o)

$(NAME)	:	$(OBJ)
		$(CC) -Wall -Wextra -fPIC $(OBJ) -shared -o $(NAME)

all	:	$(NAME)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all
