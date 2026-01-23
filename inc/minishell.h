/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:28:22 by wael              #+#    #+#             */
/*   Updated: 2026/01/23 12:07:22 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>

// global
extern int	g_sig;

// structures
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	int				type;
	char			*file;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_token
{
	int				type;
	char			*value;
	int				index;
	char			*input;
	t_env			*env_list;
	struct s_token	*next; // void *next;
}	t_token;

typedef struct s_cmd
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
	WORD, // Un mot classique (ls, -l, echo, "texte")
	PIPE, // |
	REDIR_IN, // <
	REDIR_OUT, // >
	HEREDOC, // <<
	APPEND, // >>
	CMD, // Le nom de la commande
	ARG, // Un argument
	FILE_IN, // Fichier après <
	FILE_OUT, // Fichier après > ou >>
	LIMITER, // Le mot-clé après <<
	FILE_APPEND, // Fichier après >>
}	t_token_type;

// MACRO
# define IN_SINGLE_QUOTE 1
# define IN_DOUBLE_QUOTE 2

// env.c
t_env	*init_env(char **envp);
void	free_env(t_env *env);
char	**env_to_array(t_env *env);
char	*get_env_val(t_env *env, char *name);
void	set_env_val(t_env **env, char *name, char *value);

// token.c
void	free_tokens(t_token *token);

// parsing
t_cmd	*parse_tokens(t_token *tokens, t_env *env);
char	*expand_token_value(char *str, t_env *env);

// execution
void	free_cmds(t_cmd *cmds);
char	*find_path(char *cmd, char **envp);
int		handle_redirections(t_cmd *cmd);
void	setup_child_signals(void);
void	setup_parent_signals(void);
void	execute_cmds(t_cmd *cmds, t_env **env);

// built-ins
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_cd(char **args, t_env **env);
int		ft_env(t_env *env);
int		ft_export(char **args, t_env **env);
int		ft_unset(char **args, t_env **env);
int		ft_exit(char **args);

void	print_signature(void);

#endif
