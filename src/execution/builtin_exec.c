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

int	is_valid_id(char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	print_id_error(char *arg)
{
	write(2, "minishell: export: `", 20);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

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
