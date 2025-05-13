NAME	= libglad.a
SDIR	= src/
SRC		= $(SDIR)glad.c
OBJ		= $(SRC:.c=.o)

CC		= gcc
AR		= ar rcs
CFLAGS	= -Iinclude
RM		= rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
			$(AR) $@ $^

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re