/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:15:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/14 10:00:00 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

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

static pid_t	fork_and_exec(t_cmd *tmp, t_env **env, int prev_fd, int *pfd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (tmp->next)
			close(pfd[0]);
		execute_child(tmp, env, prev_fd);
	}
	return (pid);
}

static void	exec_loop(t_cmd *tmp, t_env **env, pid_t *last_pid)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	while (tmp)
	{
		handle_pipe(tmp, pipe_fd);
		pid = fork_and_exec(tmp, env, prev_fd, pipe_fd);
		if (pid == -1)
			return ;
		handle_parent(tmp, &prev_fd, pipe_fd);
		if (!tmp->next)
			*last_pid = pid;
		tmp = tmp->next;
	}
}

int	execute_cmds(t_cmd *cmds, t_env **env)
{
	pid_t	last_pid;

	last_pid = -1;
	if (cmds && !cmds->next && cmds->args
		&& cmds->args[0] && is_builtin(cmds->args[0]))
		return (exec_single_builtin(cmds, env));
	signal(SIGINT, SIG_IGN);
	exec_loop(cmds, env, &last_pid);
	wait_children(last_pid);
	setup_parent_signals();
	return (0);
}
