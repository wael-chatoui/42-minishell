/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 10:00:00 by wael              #+#    #+#             */
/*   Updated: 2026/02/14 10:00:00 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

extern int	g_sig;

void	wait_children(pid_t last_pid)
{
	int		status;
	pid_t	pid;

	pid = waitpid(last_pid, &status, 0);
	if (pid > 0)
	{
		if (WIFEXITED(status))
			g_sig = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_sig = 128 + WTERMSIG(status);
	}
	while (wait(NULL) > 0)
		;
}

static void	restore_fds(int saved_in, int saved_out)
{
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

int	exec_single_builtin(t_cmd *cmds, t_env **env)
{
	int	saved_in;
	int	saved_out;
	int	ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (handle_redirections(cmds))
	{
		g_sig = 1;
		restore_fds(saved_in, saved_out);
		return (0);
	}
	ret = execute_builtin(cmds, env);
	restore_fds(saved_in, saved_out);
	if (ret == -1)
		return (1);
	g_sig = ret;
	return (0);
}
