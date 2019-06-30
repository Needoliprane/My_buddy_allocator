##
## EPITECH PROJECT, 2019
## makefile
## File description:
## makefile
##

CC	=	gcc

CFLAGS	=	 -fpic

CPPFLAGS =	-I./include

RM	=	rm -f

NAME	=	libmy_malloc.so

SRCPATH	=	src/

LIBPATH = 	lib/

SRC	=	$(SRCPATH)malloc.c			\
		$(SRCPATH)realloc.c			\
		$(SRCPATH)free.c			\

OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ)

test_run:
	make -C./tests
	mv tests/unit_tests .
	./unit_tests

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) libmy_malloc.so

re:	fclean all

.PHONY:	all clean fclean re
