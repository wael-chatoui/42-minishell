/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:05:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/01 00:32:40 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

/*
** Handles heredoc redirection
** @param limiter: The delimiter string for the heredoc
** @return: The file descriptor of the read end of the pipe
*/
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

static int	open_file(t_redir *tmp)
{
	int	fd;

	fd = -1;
	if (tmp->type == REDIR_IN)
		fd = open(tmp->file, O_RDONLY);
	else if (tmp->type == REDIR_OUT)
		fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->type == APPEND)
		fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(tmp->file);
		return (1);
	}
	if (tmp->type == REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

/*
** Handles all file redirections for a command
** @param cmd: The command structure
** @return: 0 on success, 1 on failure
*/
int	handle_redirections(t_cmd *cmd)
{
	t_redir	*tmp;
	int		fd;

	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			fd = handle_heredoc(tmp->file);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else
		{
			if (open_file(tmp))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
