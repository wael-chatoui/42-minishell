/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchatoui <wchatoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:28:22 by wael              #+#    #+#             */
/*   Updated: 2026/02/23 13:20:52 by wchatoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

extern int	g_sig;

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
	int				heredoc_expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_token
{
	int				type;
	char			*value;
	int				index;
	char			*input;
	t_env			*env_list;
	struct s_token	*next;
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

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	CMD,
	ARG,
	FILE_IN,
	FILE_OUT,
	LIMITER,
	FILE_APPEND,
}	t_token_type;

# define IN_SINGLE_QUOTE 1
# define IN_DOUBLE_QUOTE 2

t_env	*init_env(char **envp);
void	free_env(t_env *env);
char	**env_to_array(t_env *env);
char	*get_env_val(t_env *env, char *name);
void	set_env_val(t_env **env, char *name, char *value);
void	remove_env_var(t_env **env, char *name);
void	free_tokens(t_token *token);
t_token	*lexer(char *input);
t_token	*new_token(char *value, int type, int index);
void	token_add_back(t_token **head, t_token *new);
int		is_space(char c);
int		is_operator(char c);
t_cmd	*parse_tokens(t_token *tokens, t_env *env);
char	*expand_token_value(char *str, t_env *env);
char	*join_and_free(char *s1, char *s2);
char	*get_val(char *name, t_env *env);
char	*get_var_name(char *str);
char	*append_char(char *s, char c);
char	*append_substr(char *s, char *str, int start, int len);
t_cmd	*create_cmd(void);
void	add_redir(t_cmd *cmd, t_token *token, t_token *file_token);
int		count_args(t_token *tokens);
int		check_syntax(t_token *tokens);
int		check_unclosed_quotes(char *input);
void	free_cmds(t_cmd *cmds);
char	*find_path(char *cmd, char **envp);
int		handle_redirections(t_cmd *cmd);
int		collect_heredocs(t_cmd *cmds);
void	setup_child_signals(void);
void	setup_parent_signals(void);
int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_env **env);
void	execute_child(t_cmd *cmd, t_env **env, int prev_fd);
int		execute_cmds(t_cmd *cmds, t_env **env);
void	wait_children(pid_t last_pid);
int		exec_single_builtin(t_cmd *cmds, t_env **env);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_cd(char **args, t_env **env);
int		ft_env(t_env *env);
int		is_valid_id(char *name);
int		print_id_error(char *arg);
int		ft_export(char **args, t_env **env);
int		ft_unset(char **args, t_env **env);
int		ft_exit(char **args);
int		print_export(t_env *env);

#endif
