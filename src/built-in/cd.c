/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:25:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/01 00:23:20 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Executes the cd command
** @param args: Arguments array
** @param env: Environment list
** @return: 0 on success, 1 on failure
*/
int	ft_cd(char **args, t_env **env)
{
	char	*path;
	char	cwd[1024];

	if (!args[1])
	{
		path = get_env_val(*env, "HOME");
		if (!path)
		{
			write(2, "Minishell: cd: HOME not set\n", 28);
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	getcwd(cwd, sizeof(cwd));
	set_env_val(env, "PWD", cwd);
	return (0);
}
