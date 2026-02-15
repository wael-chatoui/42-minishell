/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:25:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/14 10:00:00 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_oldpwd(t_env **env)
{
	char	*path;

	path = get_env_val(*env, "OLDPWD");
	if (!path)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		return (NULL);
	}
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	return (path);
}

static char	*get_cd_path(char **args, t_env **env)
{
	char	*path;

	if (!args[1])
	{
		path = get_env_val(*env, "HOME");
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 27);
			return (NULL);
		}
		return (path);
	}
	if (!ft_strcmp(args[1], "-"))
		return (get_oldpwd(env));
	return (args[1]);
}

int	ft_cd(char **args, t_env **env)
{
	char	*path;
	char	old_cwd[1024];
	char	new_cwd[1024];

	if (args[1] && args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 33);
		return (1);
	}
	path = get_cd_path(args, env);
	if (!path)
		return (1);
	if (!getcwd(old_cwd, sizeof(old_cwd)))
		old_cwd[0] = '\0';
	if (chdir(path) != 0)
	{
		write(2, "minishell: cd: ", 15);
		perror(path);
		return (1);
	}
	if (getcwd(new_cwd, sizeof(new_cwd)))
	{
		set_env_val(env, "OLDPWD", old_cwd);
		set_env_val(env, "PWD", new_cwd);
	}
	return (0);
}
