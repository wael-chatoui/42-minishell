NAME	=	libftprintf.a
FLAGS	=	-Wall -Wextra -Werror

SRC		=	ft_printf \
			utils

SRCS	=	$(addsuffix .c, $(SRC))

OBJS	=	$(SRCS:%.c=%.o)

%.o:	%.c
		cc $(FLAGS) -c $< -o $@


# RULES

all:		$(NAME)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
