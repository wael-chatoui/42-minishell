# Clean, minimal Makefile for libft including get_next_line and ft_printf

FILES = \
	ft_isalnum \
	ft_abs \
	ft_atol \
	ft_count_words \
	ft_isalpha \
	ft_isascii \
	ft_isdigit \
	ft_isprint \
	ft_isspace \
	ft_isupper \
	ft_islower \
	ft_is_in \
	ft_memset \
	ft_bzero \
	ft_memcpy \
	ft_memmove \
	ft_memchr \
	ft_memcmp \
	ft_calloc \
	ft_strlen \
	ft_strcpy \
	ft_strlcpy \
	ft_strlcat \
	ft_substr \
	ft_strjoin \
	ft_strtrim \
	ft_strdup \
	ft_strchr \
	ft_strrchr \
	ft_strncmp \
	ft_strmapi \
	ft_strstr \
	ft_striteri \
	ft_strnstr \
	ft_toupper \
	ft_tolower \
	ft_atoi \
	ft_atoi_base \
	ft_split \
	ft_free_split \
	ft_itoa \
	ft_putchar \
	ft_putchar_fd \
	ft_putstr \
	ft_putstr_fd \
	ft_putendl_fd \
	ft_putnbr \
	ft_putnbr_fd \
	get_next_line \
	get_next_line_utils \
	ft_printf/ft_printf \
	ft_printf/utils

BONUS = \
	ft_lstnew_bonus \
	ft_lstadd_front_bonus \
	ft_lstsize_bonus \
	ft_lstadd_back_bonus \
	ft_lstlast_bonus \
	ft_lstdelone_bonus \
	ft_lstclear_bonus \
	ft_lstiter_bonus \
	ft_lstmap_bonus

SRC_FILES = $(addsuffix .c, $(FILES))
SRC_BONUS = $(addsuffix .c, $(BONUS))

.PHONY: all re fclean clean bonus

# Where to look for source files (root, printf dir, gnl, and src for future)
VPATH := .:ft_printf:gnl:src

INCLUDE_DIR = ./
NAME = libft.a
FLAGS = -Wall -Wextra -Werror
OPTIONS = -c -I $(INCLUDE_DIR)

# Object files placed in objs/ with the same basenames as the sources
OBJECTS = $(addprefix objs/,$(notdir $(SRC_FILES:.c=.o)))
OBJECTS_BONUS = $(addprefix objs/,$(notdir $(SRC_BONUS:.c=.o)))

# Ensure objs directory exists before compiling
objs/%%.o:
	@mkdir -p objs

# Pattern rule: use VPATH to find sources in listed directories
objs/%.o: %.c
	cc $(FLAGS) $(OPTIONS) $< -o $@

all: objs $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $^

bonus: $(OBJECTS) $(OBJECTS_BONUS)
	ar rcs $(NAME) $^

objs:
	mkdir -p objs

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean bonus objs
.PHONY: all re fclean clean bonus
