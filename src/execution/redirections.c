/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:05:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/14 12:00:00 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

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
		write(2, "minishell: ", 11);
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

int	handle_redirections(t_cmd *cmd)
{
	t_redir	*tmp;

	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			dup2(tmp->heredoc_fd, STDIN_FILENO);
			close(tmp->heredoc_fd);
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
