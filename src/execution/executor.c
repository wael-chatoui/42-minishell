/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:15:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/01 00:35:22 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

static void	handle_pipe(t_cmd *tmp, int *pipe_fd)
{
	if (tmp->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return ;
		}
		tmp->fd_out = pipe_fd[1];
	}
}

static void	handle_parent(t_cmd *tmp, int *prev_fd, int *pipe_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (tmp->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		*prev_fd = -1;
}

static void	exec_loop(t_cmd *tmp, t_env **env)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	setup_parent_signals();
	while (tmp)
	{
		handle_pipe(tmp, pipe_fd);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
		{
			if (tmp->next)
				close(pipe_fd[0]);
			execute_child(tmp, env, prev_fd);
		}
		else
			handle_parent(tmp, &prev_fd, pipe_fd);
		tmp = tmp->next;
	}
}

/*
** Executes a list of commands
** @param cmds: The list of commands
** @param env: The environment structure
*/
void	execute_cmds(t_cmd *cmds, t_env **env)
{
	if (cmds && !cmds->next && cmds->args
		&& cmds->args[0] && is_builtin(cmds->args[0]))
	{
		g_sig = execute_builtin(cmds, env);
		return ;
	}
	exec_loop(cmds, env);
	while (wait(NULL) > 0)
		;
}
