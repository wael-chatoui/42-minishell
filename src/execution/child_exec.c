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
#include <sys/stat.h>

static void	print_cmd_error(char *cmd, char *msg)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, msg, ft_strlen(msg));
}

static void	handle_cmd_not_found(char *cmd)
{
	struct stat	st;

	if (!cmd)
		exit(0);
	if (!ft_strchr(cmd, '/'))
	{
		print_cmd_error(cmd, ": command not found\n");
		exit(127);
	}
	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_cmd_error(cmd, ": Is a directory\n");
		exit(126);
	}
	if (access(cmd, F_OK) == 0)
	{
		print_cmd_error(cmd, ": Permission denied\n");
		exit(126);
	}
	print_cmd_error(cmd, ": No such file or directory\n");
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
	handle_cmd_not_found(cmd->args[0]);
}
