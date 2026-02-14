/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:00:00 by wael              #+#    #+#             */
/*   Updated: 2026/02/14 12:00:00 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

static void	hd_dollar(char **res, char *line, int *i, t_env *env)
{
	char	*var;
	char	*val;

	var = get_var_name(&line[*i + 1]);
	if (var && *var)
	{
		val = get_val(var, env);
		if (val)
		{
			*res = join_and_free(*res, val);
			free(val);
		}
		*i += ft_strlen(var) + 1;
		free(var);
	}
	else
	{
		*res = append_char(*res, '$');
		free(var);
		(*i)++;
	}
}

static char	*expand_hd_line(char *line, t_env *env)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			hd_dollar(&res, line, &i, env);
		else
		{
			res = append_char(res, line[i]);
			i++;
		}
	}
	return (res);
}

static int	read_heredoc(char *lim, t_env *env, int exp)
{
	int		fd[2];
	char	*line;
	char	*tmp;

	if (pipe(fd) == -1)
		return (-1);
	signal(SIGINT, heredoc_sigint);
	line = readline("> ");
	while (line && ft_strcmp(line, lim))
	{
		tmp = line;
		if (exp)
			line = expand_hd_line(tmp, env);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		if (exp)
			free(line);
		free(tmp);
		line = readline("> ");
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}

int	collect_heredocs(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				redir->heredoc_fd = read_heredoc(redir->file,
						cmd->env, redir->heredoc_expand);
				if (redir->heredoc_fd == -1)
					return (1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	setup_parent_signals();
	return (0);
}
