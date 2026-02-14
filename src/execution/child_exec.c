/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by wael              #+#    #+#             */
/*   Updated: 2026/02/01 00:58:12 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_cmd_not_found(char *cmd)
{
	if (!cmd)
		exit(0);
	if (ft_strchr(cmd, '/'))
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": No such file or directory\n", 28);
	}
	else
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
	}
	exit(127);
}

static void	redirect_io(t_cmd *cmd, int prev_fd)
{
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
}

/*
** Executes a command in a child process
** @param cmd: The command structure
** @param env: The environment structure
** @param prev_fd: The file descriptor of the previous pipe
*/
void	execute_child(t_cmd *cmd, t_env **env, int prev_fd)
{
	char	*path;
	char	**envp_arr;

	setup_child_signals();
	redirect_io(cmd, prev_fd);
	if (handle_redirections(cmd))
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (!cmd->args[0][0])
		handle_cmd_not_found(cmd->args[0]);
	if (is_builtin(cmd->args[0]))
	{
		if (execute_builtin(cmd, env) == -1)
			exit(g_sig);
		exit(g_sig);
	}
	envp_arr = env_to_array(*env);
	path = find_path(cmd->args[0], envp_arr);
	if (!path)
		handle_cmd_not_found(cmd->args[0]);
	execve(path, cmd->args, envp_arr);
	perror("execve");
	exit(1);
}
