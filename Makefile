# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wael <wael@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/22 21:22:21 by wael              #+#    #+#              #
#    Updated: 2026/01/20 20:06:46 by wael             ###   ########.fr        #
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
FT_PRINTF_DIR	=	$(INC_DIR)/42-ft_printf

# Libraries
LIBFT		=	$(LIBFT_DIR)/libft.a
FT_PRINTF	=	$(FT_PRINTF_DIR)/libftprintf.a

# Source files
SRCS		=	main.c \

# Object files
OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include flags
INCLUDES	=	-I$(INC_DIR) -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR)

# Linker flags
LDFLAGS		=	-L$(LIBFT_DIR) -lft -lreadline

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

$(FT_PRINTF):
			@echo "Building ft_printf..."
			@make -C $(FT_PRINTF_DIR) --no-print-directory


$(NAME):	$(LIBFT) $(FT_PRINTF) $(OBJS)
			@$(CC) $(OBJS) $(LIBFT) $(FT_PRINTF) $(LDFLAGS) -o $(NAME)
			@echo "✓ $(NAME) created successfully!"

clean:
			@make clean -C $(LIBFT_DIR) --no-print-directory
			@make clean -C $(FT_PRINTF_DIR) --no-print-directory
			@$(RM) -r $(OBJ_DIR)
			@echo "✗ Object files removed"

fclean:		clean
			@make fclean -C $(LIBFT_DIR) --no-print-directory
			@make fclean -C $(FT_PRINTF_DIR) --no-print-directory
			@$(RM) $(NAME)
			@echo "✗ $(NAME) removed"

re:			fclean all

norm:
			@norminette $(SRC_DIR) $(INC_DIR)/minishell.h

.PHONY:		all clean fclean re norm
