# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wael <wael@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/22 21:22:21 by wael              #+#    #+#              #
#    Updated: 2025/12/15 17:35:33 by wael             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		=	minishell

# Compiler and flags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3
RM			=	rm -f

# Directories
SRC_DIR			=	src
OBJ_DIR			=	obj
INC_DIR			=	inc
LIBFT_DIR		=	$(INC_DIR)/42-libft

# Libraries
LIBFT		=	$(LIBFT_DIR)/libft.a

# Source files
SRCS		=	main.c

# Object files
OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include flags
INCLUDES	=	-I$(INC_DIR) -I$(LIBFT_DIR)

# Linker flags
LDFLAGS		=	-L$(LIBFT_DIR) -lft

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all:		$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
			@echo "Compiled: $<"

$(LIBFT):
			@echo "Building libft..."
			@make -C $(LIBFT_DIR) --no-print-directory

$(NAME):	$(LIBFT) $(OBJS)
			@$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
			@echo "✓ $(NAME) created successfully!"

clean:
			@make clean -C $(LIBFT_DIR) --no-print-directory
			@$(RM) -r $(OBJ_DIR)
			@echo "✗ Object files removed"

fclean:		clean
			@make fclean -C $(LIBFT_DIR) --no-print-directory
			@$(RM) $(NAME)
			@echo "✗ $(NAME) removed"

re:			fclean all

norm:
			@norminette $(SRC_DIR) $(INC_DIR)/minishell.h

.PHONY:		all clean fclean re norm
