/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:00:00 by wael              #+#    #+#             */
/*   Updated: 2026/02/01 00:33:04 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks if a command is a builtin
** @param cmd: The command name
** @return: 1 if builtin, 0 otherwise
*/
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

/*
** Executes a builtin command
** @param cmd: The command structure
** @param env: The environment structure
** @return: The exit status of the builtin
*/
int	execute_builtin(t_cmd *cmd, t_env **env)
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
