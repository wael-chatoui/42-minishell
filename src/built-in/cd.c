/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:25:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/15 16:56:00 by wael             ###   ########.fr       */
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

static char	*build_raw_path(char *old_pwd, char *target)
{
	char	*raw;

	if (target[0] == '/')
		return (ft_strdup(target));
	raw = ft_strdup(old_pwd);
	raw = join_and_free(raw, "/");
	raw = join_and_free(raw, target);
	return (raw);
}

static char	*canonicalize_path(char *raw)
{
	char	**s;
	char	*stk[1024];
	int		d[2];
	char	*r;

	s = ft_split(raw, '/');
	(free(raw), d[0] = 0, d[1] = -1);
	while (s[++d[1]])
	{
		if (!ft_strcmp(s[d[1]], "..") && d[0] > 0)
			d[0]--;
		else if (ft_strcmp(s[d[1]], ".") && ft_strcmp(s[d[1]], ".."))
			stk[d[0]++] = s[d[1]];
	}
	r = ft_strdup("/");
	if (d[0] > 0)
		r = join_and_free(r, stk[0]);
	d[1] = 0;
	while (++d[1] < d[0])
		r = join_and_free(join_and_free(r, "/"), stk[d[1]]);
	d[1] = -1;
	while (s[++d[1]])
		free(s[d[1]]);
	return (free(s), r);
}

int	ft_cd(char **args, t_env **env)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	if (args[1] && args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 33);
		return (1);
	}
	path = get_cd_path(args, env);
	if (!path)
		return (1);
	old_pwd = get_env_val(*env, "PWD");
	if (!old_pwd)
		old_pwd = "";
	if (chdir(path) != 0)
	{
		write(2, "minishell: cd: ", 15);
		perror(path);
		return (1);
	}
	new_pwd = canonicalize_path(build_raw_path(old_pwd, path));
	(set_env_val(env, "OLDPWD", old_pwd), set_env_val(env, "PWD", new_pwd));
	free(new_pwd);
	return (0);
}
