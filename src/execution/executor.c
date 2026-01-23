/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:15:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/01/23 13:15:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

extern int	g_sig;

static int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") || \
		!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") || \
		!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

static int	execute_builtin(t_cmd *cmd, t_env **env)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd->args));
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(cmd->args, env));
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(*env));
	if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(cmd->args, env));
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(cmd->args, env));
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(cmd->args));
	return (1);
}

static void	execute_child(t_cmd *cmd, t_env **env, int prev_fd)
{
	char	*path;
	char	**envp_arr;

	setup_child_signals();
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	if (cmd->fd_in != -1)
		close(cmd->fd_in);

	if (handle_redirections(cmd))
		exit(1);

	if (!cmd->args || !cmd->args[0])
		exit(0);

	if (is_builtin(cmd->args[0]))
		exit(execute_builtin(cmd, env));

	envp_arr = env_to_array(*env);
	path = find_path(cmd->args[0], envp_arr);
	if (!path)
	{
		write(2, "Minishell: command not found: ", 30);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, "\n", 1);
		exit(127);
	}
	execve(path, cmd->args, envp_arr);
	perror("execve");
	exit(1);
}

void	execute_cmds(t_cmd *cmds, t_env **env)
{
	t_cmd	*tmp;
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	if (cmds && !cmds->next && cmds->args && cmds->args[0] && is_builtin(cmds->args[0]))
	{
		execute_builtin(cmds, env);
		return ;
	}

	prev_fd = -1;
	tmp = cmds;
	setup_parent_signals();
	while (tmp)
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
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (tmp->next)
			{
				close(pipe_fd[1]);
				prev_fd = pipe_fd[0];
			}
			else
				prev_fd = -1;
		}
		tmp = tmp->next;
	}
	while (wait(NULL) > 0)
		;
}
