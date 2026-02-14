# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wael <wael@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/22 21:22:21 by wael              #+#    #+#              #
#    Updated: 2026/02/01 00:35:24 by wael             ###   ########.fr        #
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
SRCS		=	main.c \
				env.c \
				env_utils.c \
				env_modify.c \
				token.c \
				built-in/echo.c \
				built-in/cd.c \
				built-in/builtins_extra.c \
				built-in/export_print.c \
				parsing/parser.c \
				parsing/lexer.c \
				parsing/lexer_utils.c \
				parsing/expander.c \
				parsing/expander_utils.c \
				parsing/parser_utils.c \
				parsing/syntax.c \
				execution/exec_utils.c \
				execution/child_exec.c \
				execution/builtin_exec.c \
				execution/redirections.c \
				execution/signals.c \
				execution/executor.c \
				execution/executor_utils.c \
				execution/heredoc.c

# Object files
OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include flags
INCLUDES	=	-I$(INC_DIR) -I$(LIBFT_DIR)

# Linker flags
LDFLAGS		=	-L$(LIBFT_DIR) -lft -lreadline

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all:		$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			@mkdir -p $(dir $@)
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
			@norminette $(SRC_DIR) $(INC_DIR)

.PHONY:		all clean fclean re norm
