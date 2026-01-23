/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:05:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/01/23 13:05:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	handle_heredoc(char *limiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

int	handle_redirections(t_cmd *cmd)
{
	t_redir	*tmp;
	int		fd;

	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
		{
			fd = open(tmp->file, O_RDONLY);
			if (fd == -1)
			{
				perror(tmp->file);
				return (1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (tmp->type == REDIR_OUT)
		{
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(tmp->file);
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (tmp->type == APPEND)
		{
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror(tmp->file);
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (tmp->type == HEREDOC)
		{
			// The file field in REDIR struct should contain the limiter for HEREDOC token?
			// Wait, in parser I stored the next token value as 'file'.
			// Logic: in HEREDOC, 'file' is the limiter.
			fd = handle_heredoc(tmp->file);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		tmp = tmp->next;
	}
	return (0);
}
