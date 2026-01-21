/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:28:22 by wael              #+#    #+#             */
/*   Updated: 2026/01/20 20:22:00 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../inc/42-libft/libft.h"
# include "ft_printf.h"
# include <readline/readline.h>

// global
extern int g_sig;

// structures
typedef struct	s_env
{
	char			*name;
	char			*value;
	struct	s_env	*next;
}	t_env;

typedef struct	s_redir
{
	int				type;
	char			*file;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct	s_token
{
	int				type;
	char			*value;
	int				index;
	char			*input;
	t_env			*env_list;
	struct s_token	*next; // void *next;
}	t_token;

typedef struct	s_cmd
{
	char			**args;
	t_redir			*redir;
	int				fd_in;
	int				fd_out;
	t_token			*token;
	t_env			*env;
	struct s_cmd	*next;
	struct s_cmd	*head;
}	t_cmd;

// enums
typedef enum e_token_type
{
	WORD,        // Un mot classique (ls, -l, echo, "texte")
	PIPE,        // |
	REDIR_IN,    // <
	REDIR_OUT,   // >
	HEREDOC,     // <<
	APPEND,      // >>
	CMD,         // Le nom de la commande
	ARG,         // Un argument
	FILE_IN,     // Fichier après <
	FILE_OUT,    // Fichier après > ou >>
	LIMITER,     // Le mot-clé après <<
	FILE_APPEND, // Fichier après >>
}	t_token_type;

//colors
# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"
# define BLUE    "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN    "\033[1;36m"
# define RESET   "\033[0m"

// MACRO
# define IN_SINGLE_QUOTE 1
# define IN_DOUBLE_QUOTE 2

#endif
